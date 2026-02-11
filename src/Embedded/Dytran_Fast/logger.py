import serial
import struct
import csv

PORT = 'COM4'
BAUD = 3_000_000

ser = serial.Serial(PORT, BAUD, timeout=1)

PACKET_FMT = '<2s I 6h B'
PACKET_SIZE = struct.calcsize(PACKET_FMT)

def crc8(data):
    c = 0
    for b in data:
        c ^= b
    return c

with open('logs/762rpm.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['time_us', 'ax_g', 'ay_g', 'az_g', 'gx_g', 'gy_g', 'gz_g'])

    while True:
        # sync to header
        if ser.read(1) != b'\xAA':
            continue
        if ser.read(1) != b'\x55':
            continue

        rest = ser.read(PACKET_SIZE - 2)
        if len(rest) != PACKET_SIZE - 2:
            continue

        packet = b'\xAA\x55' + rest

        # CRC check
        if crc8(packet[:-1]) != packet[-1]:
            continue

        _, t, ax, ay, az, gx, gy, gz, _ = struct.unpack(PACKET_FMT, packet)

        # milli-g → g
        writer.writerow([
            t,
            ax / 1000.0,
            ay / 1000.0,
            az / 1000.0,
            gx / 1000.0,
            gy / 1000.0,
            gz / 1000.0
        ])
