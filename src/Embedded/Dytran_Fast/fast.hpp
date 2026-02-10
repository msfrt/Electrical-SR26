#ifndef FAST_STMM_HPP
#define FAST_STMM_HPP

#include <stdint.h>
#include <stddef.h>

#pragma pack(push, 1)
struct IMUPacket {
  uint8_t header[2];   // 0xAA 0x55
  uint32_t micros;
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  uint8_t crc;
};
#pragma pack(pop)

inline int16_t voltage_to_millig(float v) {
  return (int16_t)((v / 11.75f) * 1000.0f);
}

inline uint8_t computeCRC(uint8_t *data, size_t len) {
  uint8_t crc = 0;
  for (size_t i = 0; i < len; i++) crc ^= data[i];
  return crc;
}



#endif
