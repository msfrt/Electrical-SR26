import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import yaml

import getters
# import functions

## import characterizations (python dictionary structure)
pack = getters.Pack("characterization/pack.yaml")
motor = getters.Motor("characterization/motor.yaml")
motor_controller = getters.MotorController("characterization/motor_controller.yaml")
vehicle = getters.Vehicle("characterization/vehicle.yaml")
track = getters.Track("characterization/track.yaml")

sim = getters.Simulation(vehicle, motor, pack, track)

# for seg in track.segments:
#     print(seg)

v, energy, lap_time, time_hist, energy_hist, power_hist = sim.run()

print("Lap Time:", lap_time)
print("Lap Energy (kWh):", energy/3.6e6)

# plt.figure()
# plt.plot(v)
# plt.ylabel("Speed (m/s)")
# plt.xlabel("Distance (m)")
# plt.title("Vehicle Speed Profile")
# plt.show()

# energy_kwh = energy_hist / 3.6e6
# plt.figure()
# plt.plot(time_hist, energy_kwh)
# plt.xlabel("Time (s)")
# plt.ylabel("Energy Used (kWh)")
# plt.title("Battery Energy Consumption Over Time")
# plt.grid()
# plt.show()

# plt.figure()
# plt.plot(time_hist, power_hist/1000)
# plt.xlabel("Time (s)")
# plt.ylabel("Electrical Power (kW)")
# plt.title("Power Draw Over Time")
# plt.grid()
# plt.show()

# energy_kwh = energy_hist / 3.6e6

# fig, axs = plt.subplots(1, 3, figsize=(15,5))

# # Speed vs distance
# axs[0].plot(v)
# axs[0].set_ylabel("Speed (m/s)")
# axs[0].set_xlabel("Distance (m)")
# axs[0].set_title("Vehicle Speed Profile")
# axs[0].grid()

# # Energy vs time
# axs[1].plot(time_hist, energy_kwh)
# axs[1].set_xlabel("Time (s)")
# axs[1].set_ylabel("Energy Used (kWh)")
# axs[1].set_title("Battery Energy Consumption")
# axs[1].grid()

# # Power vs time
# axs[2].plot(time_hist, power_hist/1000)
# axs[2].set_xlabel("Time (s)")
# axs[2].set_ylabel("Electrical Power (kW)")
# axs[2].set_title("Power Draw")
# axs[2].grid()

# plt.tight_layout()
# plt.show()

fig, axs = plt.subplots(2, 2, figsize=(6,6))

distance_v = np.arange(len(v)) * sim.dx
distance_e = np.arange(len(energy_hist)) * sim.dx
energy_kwh = energy_hist / 3.6e6

# Speed
axs[0,0].plot(distance_v, v)
axs[0,0].set_title("Speed Profile")
axs[0,0].set_xlabel("Distance (m)")
axs[0,0].set_ylabel("Speed (m/s)")
axs[0,0].grid()

# # Energy vs time
# axs[0,1].plot(distance_e, energy_kwh)
# axs[0,1].set_title("Energy vs Time")
# axs[0,1].set_xlabel("Distance (m)")
# axs[0,1].set_ylabel("Energy (kWh)")
# axs[0,1].grid()

# Power vs time
axs[1,0].plot(distance_e, power_hist/1000)
axs[1,0].set_title("Power Draw")
axs[1,0].set_xlabel("Distance (m)")
axs[1,0].set_ylabel("Power (kW)")
axs[1,0].grid()

# Energy vs distance
axs[1,1].plot(distance_e, energy_kwh)
axs[1,1].set_title("Energy vs Distance")
axs[1,1].set_xlabel("Distance (m)")
axs[1,1].set_ylabel("Energy (kWh)")
axs[1,1].grid()

plt.tight_layout()
plt.show()