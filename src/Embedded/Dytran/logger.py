import serial
import csv

ser = serial.Serial('COM4', 115200, timeout=1)

with open('logs/sweep.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['time_ms', 'ax_raw', 'ay_raw', 'az_raw', 'gx_raw', 'gy_raw', 'gz_raw'])

    while True:
        line = ser.readline().decode().strip()
        if line:
            writer.writerow(line.split(','))