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

v, energy, lap_time = sim.run()

print("Lap Time:", lap_time)
print("Lap Energy (kWh):", energy/3.6e6)

plt.figure()
plt.plot(v)
plt.ylabel("Speed (m/s)")
plt.xlabel("Distance (m)")
plt.title("Vehicle Speed Profile")
plt.show()