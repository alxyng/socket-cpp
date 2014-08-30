#include "Buffer.h"

#include <arpa/inet.h>
#include <cstdint>

Buffer::Buffer(uint32_t size) {
  this->raw.reserve(size);
  this->raw.clear();

  this->position = 0;
}

void Buffer::writeUInt8(uint8_t value) {
  this->append<uint8_t>(value);
}

void Buffer::writeUInt16BE(uint16_t value) {
  if (!Buffer::isMachineBigEndian())
      Buffer::swapByteOrder(&value, 2);
  this->append<uint16_t>(value);
}

void Buffer::writeUInt16LE(uint16_t value) {
  if (Buffer::isMachineBigEndian())
    Buffer::swapByteOrder(&value, 2);
  this->append<uint16_t>(value);
}

uint8_t Buffer::readUInt8(uint32_t index) const {
  return read<uint8_t>(index);
}

uint16_t Buffer::readUInt16BE(uint32_t index) const {
  uint16_t value = read<uint16_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder(&value, 2);

  return value;
}

uint16_t Buffer::readUInt16LE(uint32_t index) const {
  uint16_t value = read<uint16_t>(index);

  if (isMachineBigEndian())
      swapByteOrder(&value, 2);

  return value;
}
