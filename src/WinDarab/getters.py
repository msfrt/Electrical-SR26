import yaml
import numpy as np

class Pack:
    def __init__(self, yaml_file):
        with open(yaml_file, "r") as f:
            data = yaml.safe_load(f)

        pack = data["pack"]

        self.series = pack["configuration"]["series_cells"]
        self.parallel = pack["configuration"]["parallel_cells"]
        self.max_current = pack["limits"]["max_current_A"]
        self.nominal_voltage = pack["nominal"]["nominal_voltage_V"]
        self.internal_impedance = pack["nominal"]["internal_impedance_mOhm"]
        self.capacity = pack["nominal"]["nominal_capacity_Ah"]
        self.min_voltage = pack["limits"]["min_voltage_V"]
        self.max_voltage = pack["limits"]["max_voltage_V"]

        self.SOC = 1 ## beginning SOC, assuming 100%
        self.min_SOC = pack["limits"]["min_SOC"]

        self.peak_current = 0
        # self.min_voltage = self.nominal_voltage

    # def update(self, electrical_power, dt):
    #     I = electrical_power / self.nominal_voltage
    #     self.SOC -= I*dt/(self.capacity*3600)
    #     return I, self.SOC
    
    def ocv(self):
        return self.nominal_voltage*(0.9+0.1*self.SOC) ## simplified
    
    def solve_current(self, power_request): ## includes voltage sag
        V_oc = self.ocv()

        a = self.internal_impedance/1000
        b = -V_oc
        c = power_request

        disc = b**2-4*a*c
        if disc < 0:
            return self.max_current
        
        I = (-b - np.sqrt(disc)) / (2*a)

        return min(I, self.max_current)
    
    def draw_power(self, power_request, dt):

        I = self.solve_current(power_request)
        V = self.ocv()-I*self.internal_impedance/1000
        P = V*I
        self.SOC -= I*dt/(self.capacity*3600)

        return P, V, I

class Motor:
    def __init__(self, yaml_file):
        with open(yaml_file, "r") as f:
            data = yaml.safe_load(f)

        motor = data["motor"]

        self.max_speed = motor["limits"]["max_speed_rpm"]
        self.max_torque = motor["limits"]["max_torque_Nm"]
        self.max_power = motor["limits"]["max_power_kW"]
        self.torque_constant = motor["constants"]["torque_constant_Nm_per_A"]
        self.phase_resistance = motor["constants"]["phase_resistance_mOhm"]
        self.efficiency = motor["efficiency"]["constant"]

    def torque(self, rpm): ## torque region vs. power region of typical motor curve
        omega = rpm*2*np.pi/60
        omega_base = (self.max_power*1000) / self.max_torque
        # print(omega, omega_base, rpm)
        if omega <= omega_base:
            return self.max_torque
        elif omega <= self.max_speed*2*np.pi/60:
            return (self.max_power*1000) / omega
        else:
            return 0.0
    
    # def efficiency(self, torque, rpm): ## come back here, this is useful for an efficiency map
    #     pass

class MotorController:
    def __init__(self, yaml_file):
        with open(yaml_file, "r") as f:
            data = yaml.safe_load(f)

        motorController = data["motor_controller"]

        self.max_voltage = motorController["limits"]["max_dc_voltage_V"]
        self.max_current = motorController["limits"]["max_dc_current_A"]
        self.max_power = motorController["limits"]["max_power_kW"]
        self.regen_power = motorController["regen"]["max_regen_power_kW"]
        self.efficiency = motorController["efficiency"]["constant"]

class Vehicle:
    def __init__(self, yaml_file):
        with open(yaml_file, "r") as f:
            data = yaml.safe_load(f)

        vehicle = data["vehicle"]

        self.mass = vehicle["overview"]["mass_kg"]
        self.gear_ratio = vehicle["overview"]["gear_ratio"]
        self.mu = vehicle["overview"]["friction_coefficient"]
        self.wheel_radius = vehicle["overview"]["wheel_radius_m"]
        self.Crr = vehicle["efficiency"]["rolling_resistance_coefficient"]
        self.drivetrain_efficiency = vehicle["efficiency"]["drivetrain_efficiency"]
        
        self.frontal_area = vehicle["aerodynamics"]["frontal_area_m2"]
        self.Cd = vehicle["aerodynamics"]["drag_coefficient"]
        self.Cl = vehicle["aerodynamics"]["lift_coefficient"]

class Track:
    def __init__(self, yaml_file):
        with open(yaml_file, "r") as f:
            data = yaml.safe_load(f)

        track = data["track"]

        self.air_density = track["overview"]["p_kg/m3"]
        self.total_length = track["overview"]["total_length_m"]
        self.segments = track["segments"]
        self.power_limit = track["overview"]["power_limit"]

class Simulation:
    def __init__(self, vehicle, motor, pack, track):
        # self.velocity = 0.0
        self.vehicle = vehicle
        self.motor = motor
        self.pack = pack
        self.track = track
        
        self.dx = 1 ## 1m step
    
    def build_track(self):
        radius = []
        throttle = []

        for seg in self.track.segments:
            steps = int(seg["length_m"]/self.dx)
            t = seg["throttle"]
            
            if seg["type"] == "corner":
                r = seg["radius_m"]
            else:
                r = 1e6
            
            for _ in range(steps):
                radius.append(r)
                throttle.append(t)
                # print(t)
                
        # print(np.array(throttle))

        return np.array(radius), np.array(throttle)

    def calculate_corner_limits(self, radius):  
        v_corner = np.sqrt(self.vehicle.mu * 9.81 * radius)
        
        return v_corner

    def calculate_drive_force(self, v, throttle):
        wheel_rpm = (v / (2*np.pi*self.vehicle.wheel_radius)) * 60
        motor_rpm = wheel_rpm * self.vehicle.gear_ratio
        # print(motor_rpm)## actually put in the right relationship pls
        
        torque = throttle * self.motor.torque(motor_rpm)
       
        F = torque * self.vehicle.gear_ratio / self.vehicle.wheel_radius

        # print(torque)

        return F
    
    def calculate_drag_force(self, v):
        return 0.5 * self.track.air_density * (self.vehicle.Cd * self.vehicle.frontal_area) * v**2
        #return 0.5 * self.track.air_density * (0.8) * v**2

    def calculate_rolling_force(self):
        return self.vehicle.Crr * self.vehicle.mass * 9.81
    
    def forward_pass(self, v_corner, throttle):
        N = len(v_corner)
        v = np.zeros(N)
        # tr = np.zeros(N)

        for i in range(N-1):
            F_drive = self.calculate_drive_force(v[i], throttle[i]) ## throttle to scale the drive torque
            # print(v[i], throttle[i], F_drive)
            F_drag = self.calculate_drag_force(v[i])
            # print(F_drag)
            F_roll = self.calculate_rolling_force()

            F_net = F_drive - F_drag - F_roll

            a = F_net / self.vehicle.mass

            v_next = np.sqrt(max(v[i]**2 + 2*a*self.dx, 0))

            v[i+1] = min(v_next, v_corner[i+1])

        return v
    
    def reverse_pass(self, v):
        N = len(v)

        a_brake = self.vehicle.mu * 9.81

        for i in reversed(range(N-1)):

            v_brake = np.sqrt(v[i+1]**2 + 2*a_brake*self.dx)

            v[i] = min(v[i], v_brake)

        return v
    
    # def compute_energy(self, v, throttle):

    #     energy = 0
    #     time = 0

    #     time_hist = []
    #     energy_hist = []
    #     power_hist = []

    #     for i in range(len(v)-1):

    #         v_avg = (v[i] + v[i+1]) / 2

    #         if v_avg < 0.1:
    #             continue

    #         dt = self.dx / v_avg

    #         F_drive = self.calculate_drive_force(v_avg, throttle[i])

    #         power_mech = F_drive * v_avg
    #         power_elec = power_mech / self.motor.efficiency

    #         energy += power_elec * dt
    #         time += dt

    #         time_hist.append(time)
    #         energy_hist.append(energy)
    #         power_hist.append(power_elec)

    #     return energy, time, np.array(time_hist), np.array(energy_hist), np.array(power_hist)
    
    def compute_energy(self, v, throttle):

        energy = 0
        time = 0

        time_hist = []
        energy_hist = []
        power_hist = []

        regen_eff = 0.97 ## efficiency of motor controller assumed
        regen_limit = self.track.power_limit * 1000

        for i in range(len(v)-1):

            v_avg = (v[i] + v[i+1]) / 2

            if v_avg < 0.1:
                continue

            dt = self.dx / v_avg

            a = (v[i+1] - v[i]) / dt

            if a >= 0:
                # ACCELERATION

                F_drive = self.calculate_drive_force(v_avg, throttle[i])

                power_mech = F_drive * v_avg
                power_elec = power_mech / self.motor.efficiency

            else:
                # # BRAKING / REGEN

                # F_brake = self.vehicle.mass * abs(a)

                # power_mech = F_brake * v_avg

                # power_elec = -regen_eff * power_mech

                # # limit regen power
                # power_elec = max(power_elec, -regen_limit)
                
                # BRAKING / REGEN
                F_total_brake = self.vehicle.mass * abs(a)

                # Split forces based on 60/40 bias
                F_front_friction = F_total_brake * 0.60
                F_rear_total = F_total_brake * 0.40

                # Mechanical power at the rear axle (where the motor is)
                power_mech_rear = F_rear_total * v_avg

                ## RWD single motor things
                # Apply regen efficiency only to the rear mechanical power
                power_elec = -regen_eff * power_mech_rear

                # Limit regen power (battery/motor constraint)
                # Note: This limits electrical recovery, not the physical braking force
                power_elec = max(power_elec, -regen_limit)

            energy += power_elec * dt
            time += dt

            time_hist.append(time)
            energy_hist.append(energy)
            power_hist.append(power_elec)

        return energy, time, np.array(time_hist), np.array(energy_hist), np.array(power_hist)

    def build_xy_track(self):

        x = [0.0]
        y = [0.0]

        heading = -1  # radians (0 = along +x)

        for seg in self.track.segments:

            length = seg["length_m"]
            steps = int(length / self.dx)

            if seg["type"] == "corner":

                R = seg["radius_m"]

                # default to left turn if not specified
                direction = seg.get("direction", "left")

                dtheta = self.dx / R  # curvature

                for _ in range(steps):

                    if direction == "left":
                        heading += dtheta
                    else:
                        heading -= dtheta

                    x.append(x[-1] + self.dx * np.cos(heading))
                    y.append(y[-1] + self.dx * np.sin(heading))

            else:  # straight

                for _ in range(steps):
                    x.append(x[-1] + self.dx * np.cos(heading))
                    y.append(y[-1] + self.dx * np.sin(heading))

        return np.array(x), np.array(y)

    def plot_track_speed(self, v):

        import matplotlib.pyplot as plt

        x, y = self.build_xy_track()

        # match lengths
        N = min(len(x), len(v))
        x = x[:N]
        y = y[:N]
        v = v[:N]

        plt.figure(figsize=(8,8))

        sc = plt.scatter(x, y, c=v, s=6)

        plt.colorbar(sc, label="Speed (m/s)")

        plt.title("Track Map Colored by Speed")
        plt.xlabel("X (m)")
        plt.ylabel("Y (m)")

        plt.axis("equal")
        plt.grid()

        plt.show()

    def plot_track_power(self, power_hist):

        import matplotlib.pyplot as plt

        x, y = self.build_xy_track()

        # match lengths
        N = min(len(x), len(power_hist))
        x = x[:N]
        y = y[:N]
        power = power_hist[:N] / 1000  # convert to kW

        plt.figure(figsize=(8,8))

        sc = plt.scatter(x, y, c=power, s=6)

        plt.colorbar(sc, label="Electrical Power (kW)")

        plt.title("Track Map Colored by Power")
        plt.xlabel("X (m)")
        plt.ylabel("Y (m)")

        plt.axis("equal")
        plt.grid()

        plt.show()

    def plot_track_speed_power(self, v, power_hist):

        import matplotlib.pyplot as plt
        import matplotlib.colors as mcolors
        import numpy as np

        x, y = self.build_xy_track()

        N = min(len(x), len(v), len(power_hist))
        x = x[:N]
        y = y[:N]
        v = v[:N]
        power = power_hist[:N] / 1000  # kW

        fig, axs = plt.subplots(1, 2, figsize=(10,4))

        # --- Speed ---
        sc1 = axs[0].scatter(x, y, c=v, s=6)
        axs[0].set_title("Speed (m/s)")
        axs[0].axis("equal")
        axs[0].grid()
        fig.colorbar(sc1, ax=axs[0])

        # --- Power ---
        pmin = np.min(power)
        pmax = np.max(power)

        if pmin < 0 and pmax > 0:
            norm = mcolors.TwoSlopeNorm(vmin=pmin, vcenter=0, vmax=pmax)
            cmap = "coolwarm"
        else:
            norm = None
            cmap = "viridis"

        sc2 = axs[1].scatter(x, y, c=power, s=6, cmap=cmap, norm=norm)
        axs[1].set_title("Power (kW)")
        axs[1].axis("equal")
        axs[1].grid()
        fig.colorbar(sc2, ax=axs[1])

        plt.tight_layout()
        plt.show()

    def run(self):
        radius, throttle = self.build_track() ## eventually use throttle to scale drive force

        v_corner = self.calculate_corner_limits(radius)

        v = self.forward_pass(v_corner, throttle)

        v = self.reverse_pass(v)

        # energy, lap_time = self.compute_energy(v, throttle)

        energy, lap_time, time_hist, energy_hist, power_hist = self.compute_energy(v, throttle)

        return v, energy, lap_time, time_hist, energy_hist, power_hist