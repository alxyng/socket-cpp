#include "Buffer.h"

#include <cstdint>
#include <string>

Buffer::Buffer(uint32_t size) {
  this->raw.reserve(size);
  this->raw.clear();

  this->position = 0;
}

void Buffer::writeInt8(int8_t value) {
  this->append<int8_t>(value);
}

void Buffer::writeInt8(int8_t value, uint32_t index) {
  this->insert<int8_t>(value, index);
}

void Buffer::writeUInt8(uint8_t value) {
  this->append<uint8_t>(value);
}

void Buffer::writeUInt8(uint8_t value, uint32_t index) {
  this->insert<uint8_t>(value, index);
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

// TODO: research std::string address contiguousy - new stanard forces
//       memory to be contiguous but not sure if it is yet
void Buffer::writeString(std::string& str) {
  for (std::string::iterator it = str.begin(); it != str.end(); it++)
    this->append<int8_t>(*it);
}

int8_t Buffer::readInt8(uint32_t index) const {
  return read<int8_t>(index);
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

int32_t Buffer::readInt32BE(uint32_t index) const {
  int32_t value = read<int32_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder(&value, 4);

  return value;
}

int32_t Buffer::readInt32LE(uint32_t index) const {
  int32_t value = read<int32_t>(index);

  if (isMachineBigEndian())
      swapByteOrder(&value, 4);

  return value;
}

uint32_t Buffer::readUInt32BE(uint32_t index) const {
  uint32_t value = read<uint32_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder(&value, 4);

  return value;
}

uint32_t Buffer::readUInt32LE(uint32_t index) const {
  uint32_t value = read<uint32_t>(index);

  if (isMachineBigEndian())
      swapByteOrder(&value, 4);

  return value;
}

int64_t Buffer::readInt64BE(uint32_t index) const {
  int64_t value = read<int64_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder(&value, 8);

  return value;
}

int64_t Buffer::readInt64LE(uint32_t index) const {
  int64_t value = read<int64_t>(index);

  if (isMachineBigEndian())
      swapByteOrder(&value, 8);

  return value;
}

uint64_t Buffer::readUInt64BE(uint32_t index) const {
  uint64_t value = read<uint64_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder(&value, 8);

  return value;
}

uint64_t Buffer::readUInt64LE(uint32_t index) const {
  uint64_t value = read<uint64_t>(index);

  if (isMachineBigEndian())
      swapByteOrder(&value, 8);

  return value;
}

std::string Buffer::readString(uint32_t index, uint32_t length) const {
  std::string str;

  for (uint32_t i = index; i < index + length; i++)
    str += readInt8(i);

  return str;
}

// TODO: defining custom operator functions e.g. << and >> for serialization
