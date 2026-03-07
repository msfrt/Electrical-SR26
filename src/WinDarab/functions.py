import numpy as np
import matplotlib.pyplot as plt

g = 9.81


class LapSim:

    def __init__(self, vehicle, motor, pack, track, dx=1.0):

        self.vehicle = vehicle
        self.motor = motor
        self.pack = pack
        self.track = track

        self.dx = dx

        self.mass = vehicle.mass
        self.CdA = vehicle.CdA
        self.Crr = vehicle.Crr
        self.wheel_radius = vehicle.wheel_radius
        self.gear_ratio = vehicle.gear_ratio
        self.mu = vehicle.mu

        self.rho = track.overview["p_kg/m3"]

    # ---------------------------------------------------
    # Convert track segments → 1 m mesh
    # ---------------------------------------------------

    def build_track_mesh(self):

        radius = []

        for seg in self.track.segments:

            steps = int(seg["length_m"] / self.dx)

            if seg["type"] == "corner":
                r = seg["radius_m"]
            else:
                r = 1e6  # straight = huge radius

            for _ in range(steps):
                radius.append(r)

        return np.array(radius)

    # ---------------------------------------------------
    # Max corner speeds
    # ---------------------------------------------------

    def compute_corner_limits(self, radius):

        v_corner = np.sqrt(self.mu * g * radius)

        return v_corner

    # ---------------------------------------------------
    # Motor drive force
    # ---------------------------------------------------

    def drive_force(self, v):

        wheel_rpm = (v / (2*np.pi*self.wheel_radius)) * 60
        motor_rpm = wheel_rpm * self.gear_ratio

        torque = self.motor.torque(motor_rpm)

        F = torque * self.gear_ratio / self.wheel_radius

        return F

    # ---------------------------------------------------
    # Resistive forces
    # ---------------------------------------------------

    def drag_force(self, v):

        return 0.5 * self.rho * self.CdA * v**2

    def rolling_force(self):

        return self.Crr * self.mass * g

    # ---------------------------------------------------
    # Forward pass
    # ---------------------------------------------------

    def forward_pass(self, v_corner):

        N = len(v_corner)
        v = np.zeros(N)

        for i in range(N-1):

            F_drive = self.drive_force(v[i])
            F_drag = self.drag_force(v[i])
            F_roll = self.rolling_force()

            F_net = F_drive - F_drag - F_roll

            a = F_net / self.mass

            v_next = np.sqrt(max(v[i]**2 + 2*a*self.dx, 0))

            v[i+1] = min(v_next, v_corner[i+1])

        return v

    # ---------------------------------------------------
    # Backward pass (braking)
    # ---------------------------------------------------

    def backward_pass(self, v):

        N = len(v)

        a_brake = self.mu * g

        for i in reversed(range(N-1)):

            v_brake = np.sqrt(v[i+1]**2 + 2*a_brake*self.dx)

            v[i] = min(v[i], v_brake)

        return v

    # ---------------------------------------------------
    # Energy + lap time
    # ---------------------------------------------------

    def compute_energy(self, v):

        energy = 0
        time = 0

        for i in range(len(v)-1):

            v_avg = (v[i] + v[i+1]) / 2

            if v_avg < 0.1:
                continue

            dt = self.dx / v_avg

            F_drive = self.drive_force(v_avg)

            power = F_drive * v_avg

            energy += power * dt
            time += dt

        return energy, time

    # ---------------------------------------------------
    # Main solve
    # ---------------------------------------------------

    def run(self):

        radius = self.build_track_mesh()

        v_corner = self.compute_corner_limits(radius)

        v = self.forward_pass(v_corner)

        v = self.backward_pass(v)

        energy, lap_time = self.compute_energy(v)

        return v, energy, lap_time
    

sim = LapSim(vehicle, motor, pack, track)

v, energy, lap_time = sim.run()

print("Lap Time:", lap_time)
print("Lap Energy (kWh):", energy/3.6e6)

plt.figure()
plt.plot(v)
plt.ylabel("Speed (m/s)")
plt.xlabel("Distance (m)")
plt.title("Vehicle Speed Profile")
plt.show()