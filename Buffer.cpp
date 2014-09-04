#include "Buffer.h"

#include <cstdint>
#include <cstring>
#include <string>

Buffer::Buffer(uint32_t capacity) { // size in bytes
  this->construct(capacity);
}

Buffer::Buffer(const void* const data, uint32_t size) {
  this->construct(size);
  this->writeBytes(data, size);
}

Buffer::Buffer(const void* const data, uint32_t size, uint32_t index) {
  this->construct(size);
  this->writeBytes(data, size, index);
}

Buffer::~Buffer() {
  delete this->raw;
}

void Buffer::construct(uint32_t capacity) {
  this->raw = NULL;
  this->capacity = 0;
  this->size = 0;

  this->resize(capacity);
  this->clear();
}

uint32_t Buffer::getBlockCapacity(uint32_t capacity) {
  return ((uint32_t)((capacity + BLOCK_SIZE - 1.0) / BLOCK_SIZE)) * BLOCK_SIZE;
}

// needs to preserve data and add cleared data (works in blocks)
void Buffer::resize(uint32_t capacity) {
  capacity = this->getBlockCapacity(capacity);

  if (capacity == this->capacity)
    return;

  if (this->capacity == 0 || this->size == 0) {
    delete this->raw;
    this->raw = new uint8_t[capacity];
    this->capacity = capacity;
    return;
  }

  if (this->size > capacity)
    this->size = capacity;

  uint8_t* data = new uint8_t[capacity];
  std::memcpy(data, this->raw, this->size);
  delete this->raw;
  this->raw = data;

  uint32_t oldCapacity = this->capacity;
  this->capacity = capacity;

  if (oldCapacity < this->capacity)
    clear(oldCapacity);
}

// maintains size but clears memory
void Buffer::clear(uint32_t index) {
  if (index < this->capacity)
    std::memset(&this->raw[index], 0, this->capacity - index);

  this->size = (this->size < index) ? this->size : index;
}

// reduces size (still sticks to blocks) - might not change capacity
void Buffer::erase(uint32_t length) {
  if (length < 1)
    return;

  this->size -= length;
  this->capacity = this->getBlockCapacity(this->size);

  uint8_t* data = new uint8_t[this->capacity];
  std::memcpy(data, &this->raw[length], this->size);
  delete this->raw;
  this->raw = data;
  clear(this->size);
}

void Buffer::erase(uint32_t index, uint32_t length) {
  if (index < 1) {
    this->erase(length);
    return;
  }

  this->size -= length;
  this->capacity = this->getBlockCapacity(this->size);

  uint8_t* data = new uint8_t[this->capacity];
  std::memcpy(data, this->raw, index);
  std::memcpy(&data[index], &this->raw[index + length], this->size - index);
  delete this->raw;
  this->raw = data;
  clear(this->size);
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

void Buffer::writeInt16BE(int16_t value) {
  if (!isMachineBigEndian())
      swapByteOrder<int16_t>(&value);
  this->append<int16_t>(value);
}

void Buffer::writeInt16BE(int16_t value, uint32_t index) {
  if (!isMachineBigEndian())
      swapByteOrder<int16_t>(&value);
  this->insert<int16_t>(value, index);
}

void Buffer::writeInt16LE(int16_t value) {
  if (isMachineBigEndian())
    swapByteOrder<int16_t>(&value);
  this->append<int16_t>(value);
}

void Buffer::writeInt16LE(int16_t value, uint32_t index) {
  if (isMachineBigEndian())
    swapByteOrder<int16_t>(&value);
  this->insert<int16_t>(value, index);
}

void Buffer::writeUInt16BE(uint16_t value) {
  if (!isMachineBigEndian())
      swapByteOrder<uint16_t>(&value);
  this->append<uint16_t>(value);
}

void Buffer::writeUInt16BE(uint16_t value, uint32_t index) {
  if (!isMachineBigEndian())
      swapByteOrder<uint16_t>(&value);
  this->insert<uint16_t>(value, index);
}

void Buffer::writeUInt16LE(uint16_t value) {
  if (isMachineBigEndian())
    swapByteOrder<uint16_t>(&value);
  this->append<uint16_t>(value);
}

void Buffer::writeUInt16LE(uint16_t value, uint32_t index) {
  if (isMachineBigEndian())
    swapByteOrder<uint16_t>(&value);
  this->insert<uint16_t>(value, index);
}

void Buffer::writeInt32BE(int32_t value) {
  if (!isMachineBigEndian())
      swapByteOrder<int32_t>(&value);
  this->append<int32_t>(value);
}

void Buffer::writeInt32BE(int32_t value, uint32_t index) {
  if (!isMachineBigEndian())
      swapByteOrder<int32_t>(&value);
  this->insert<int32_t>(value, index);
}

void Buffer::writeInt32LE(int32_t value) {
  if (isMachineBigEndian())
    swapByteOrder<int32_t>(&value);
  this->append<int32_t>(value);
}

void Buffer::writeInt32LE(int32_t value, uint32_t index) {
  if (isMachineBigEndian())
    swapByteOrder<int32_t>(&value);
  this->insert<int32_t>(value, index);
}

void Buffer::writeUInt32BE(uint32_t value) {
  if (!isMachineBigEndian())
      swapByteOrder<uint32_t>(&value);
  this->append<uint32_t>(value);
}

void Buffer::writeUInt32BE(uint32_t value, uint32_t index) {
  if (!isMachineBigEndian())
      swapByteOrder<uint32_t>(&value);
  this->insert<uint32_t>(value, index);
}

void Buffer::writeUInt32LE(uint32_t value) {
  if (isMachineBigEndian())
    swapByteOrder<uint32_t>(&value);
  this->append<uint32_t>(value);
}

void Buffer::writeUInt32LE(uint32_t value, uint32_t index) {
  if (isMachineBigEndian())
    swapByteOrder<uint32_t>(&value);
  this->insert<uint32_t>(value, index);
}

void Buffer::writeInt64BE(int64_t value) {
  if (!isMachineBigEndian())
      swapByteOrder<int64_t>(&value);
  this->append<int64_t>(value);
}

void Buffer::writeInt64BE(int64_t value, uint32_t index) {
  if (!isMachineBigEndian())
      swapByteOrder<int64_t>(&value);
  this->insert<int64_t>(value, index);
}

void Buffer::writeInt64LE(int64_t value) {
  if (isMachineBigEndian())
    swapByteOrder<int64_t>(&value);
  this->append<int64_t>(value);
}

void Buffer::writeInt64LE(int64_t value, uint32_t index) {
  if (isMachineBigEndian())
    swapByteOrder<int64_t>(&value);
  this->insert<int64_t>(value, index);
}

void Buffer::writeUInt64BE(uint64_t value) {
  if (!isMachineBigEndian())
      swapByteOrder<uint64_t>(&value);
  this->append<uint64_t>(value);
}

void Buffer::writeUInt64BE(uint64_t value, uint32_t index) {
  if (!isMachineBigEndian())
      swapByteOrder<uint64_t>(&value);
  this->insert<uint64_t>(value, index);
}

void Buffer::writeUInt64LE(uint64_t value) {
  if (isMachineBigEndian())
    swapByteOrder<uint64_t>(&value);
  this->append<uint64_t>(value);
}

void Buffer::writeUInt64LE(uint64_t value, uint32_t index) {
  if (isMachineBigEndian())
    swapByteOrder<uint64_t>(&value);
  this->insert<uint64_t>(value, index);
}

void Buffer::writeFloatBE(float value) {
  if (!isMachineBigEndian())
    swapByteOrder<float>(&value);
  this->append<float>(value);
}

void Buffer::writeFloatBE(float value, uint32_t index) {
  if (!isMachineBigEndian())
    swapByteOrder<float>(&value);
  this->insert<float>(value, index);
}

void Buffer::writeFloatLE(float value) {
  if (isMachineBigEndian())
    swapByteOrder<float>(&value);
  this->append<float>(value);
}

void Buffer::writeFloatLE(float value, uint32_t index) {
  if (isMachineBigEndian())
    swapByteOrder<float>(&value);
  this->insert<float>(value, index);
}

void Buffer::writeDoubleBE(double value) {
  if (!isMachineBigEndian())
    swapByteOrder<double>(&value);
  this->append<double>(value);
}

void Buffer::writeDoubleBE(double value, uint32_t index) {
  if (!isMachineBigEndian())
    swapByteOrder<double>(&value);
  this->insert<double>(value, index);
}

void Buffer::writeDoubleLE(double value) {
  if (isMachineBigEndian())
    swapByteOrder<double>(&value);
  this->append<double>(value);
}

void Buffer::writeDoubleLE(double value, uint32_t index) {
  if (isMachineBigEndian())
    swapByteOrder<double>(&value);
  this->insert<double>(value, index);
}

// TODO: research std::string address contiguousy - new standard apparently
//       forces std::string memory to be contiguous but not sure if it is yet
void Buffer::writeString(std::string& str) {
  for (std::string::iterator it = str.begin(); it != str.end(); it++)
    this->append<int8_t>(*it);
}

void Buffer::writeString(const char* const str) {
  for (int i = 0; str[i] != '\0'; i++)
    this->append<int8_t>(str[i]);
}

void Buffer::writeString(std::string& str, uint32_t index) {
  for (std::string::iterator it = str.begin(); it != str.end(); it++)
    this->insert<int8_t>(*it, index + std::distance(str.begin(), it));
}

void Buffer::writeString(const char* const str, uint32_t index) {
  for (int i = 0; str[i] != '\0'; i++)
    this->insert<int8_t>(str[i], index + i);
}

void Buffer::writeBytes(const void* const data, uint32_t length) {
  if (this->size + sizeof (data) > this->capacity)
    this->resize(this->size + sizeof (data));

  std::memcpy(&this->raw[this->size], (uint8_t*)data, length);
  this->size += length;
}

void Buffer::writeBytes(const void* data, uint32_t length, uint32_t index) {
  if (index + length > this->capacity)
    this->resize(index + length);

  std::memcpy(&this->raw[index], (uint8_t*)data, length);
  this->size += length;
}

void Buffer::writeBuffer(Buffer& buffer) {
  this->writeBytes(buffer.raw, buffer.getSize());
}

void Buffer::writeBuffer(Buffer& buffer, uint32_t index) {
  this->writeBytes(buffer.raw, buffer.getSize(), index);
}

int8_t Buffer::readInt8(uint32_t index) const {
  return read<int8_t>(index);
}

uint8_t Buffer::readUInt8(uint32_t index) const {
  return read<uint8_t>(index);
}

int16_t Buffer::readInt16BE(uint32_t index) const {
  int16_t value = read<int16_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder<int16_t>(&value);

  return value;
}

int16_t Buffer::readInt16LE(uint32_t index) const {
  int16_t value = read<int16_t>(index);

  if (isMachineBigEndian())
      swapByteOrder<int16_t>(&value);

  return value;
}

uint16_t Buffer::readUInt16BE(uint32_t index) const {
  uint16_t value = read<uint16_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder<uint16_t>(&value);

  return value;
}

uint16_t Buffer::readUInt16LE(uint32_t index) const {
  uint16_t value = read<uint16_t>(index);

  if (isMachineBigEndian())
      swapByteOrder<uint16_t>(&value);

  return value;
}

int32_t Buffer::readInt32BE(uint32_t index) const {
  int32_t value = read<int32_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder<int32_t>(&value);

  return value;
}

int32_t Buffer::readInt32LE(uint32_t index) const {
  int32_t value = read<int32_t>(index);

  if (isMachineBigEndian())
      swapByteOrder<int32_t>(&value);

  return value;
}

uint32_t Buffer::readUInt32BE(uint32_t index) const {
  uint32_t value = read<uint32_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder<uint32_t>(&value);

  return value;
}

uint32_t Buffer::readUInt32LE(uint32_t index) const {
  uint32_t value = read<uint32_t>(index);

  if (isMachineBigEndian())
      swapByteOrder<uint32_t>(&value);

  return value;
}

int64_t Buffer::readInt64BE(uint32_t index) const {
  int64_t value = read<int64_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder<int64_t>(&value);

  return value;
}

int64_t Buffer::readInt64LE(uint32_t index) const {
  int64_t value = read<int64_t>(index);

  if (isMachineBigEndian())
      swapByteOrder<int64_t>(&value);

  return value;
}

uint64_t Buffer::readUInt64BE(uint32_t index) const {
  uint64_t value = read<uint64_t>(index);

  if (!isMachineBigEndian())
      swapByteOrder<uint64_t>(&value);

  return value;
}

uint64_t Buffer::readUInt64LE(uint32_t index) const {
  uint64_t value = read<uint64_t>(index);

  if (isMachineBigEndian())
      swapByteOrder<uint64_t>(&value);

  return value;
}

std::string Buffer::readString(uint32_t index, uint32_t length) const {
  std::string str;

  for (uint32_t i = index; i < index + length; i++)
    str += readInt8(i);

  return str;
}

Buffer Buffer::readBuffer(uint32_t index, uint32_t length) const {

}

void Buffer::readBytes(void* buffer, uint32_t length, uint32_t index) const {
  std::memcpy(buffer, &this->raw[index], length);
}

// TODO: defining custom operator functions e.g. << and >> for serialization
