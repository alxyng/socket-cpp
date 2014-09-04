#ifndef BUFFER_H_
#define BUFFER_H_

// TODO: bounds check maybe

#include <cstdint>
#include <cstring>
#include <string>

class Buffer {
  private:
    uint8_t* raw;
    static const uint32_t BLOCK_SIZE = 4096;
    uint32_t size; // amount of data in buffer so far (different to capacity)
    uint32_t capacity; // capacity (increases in BLOCK_SIZE bytes)

    void construct(uint32_t capacity);
    uint32_t getBlockCapacity(uint32_t capacity);

    template <typename T> void append(T data) {
      if (this->size + sizeof (data) > this->capacity)
        this->resize(this->size + sizeof (data));

      std::memcpy(&raw[this->size], (uint8_t*)&data, sizeof (data));
      this->size += sizeof (data);
    }

    template <typename T> void insert(T data, uint32_t index) {
      if (index + sizeof (data) > this->capacity)
        this->resize(index + sizeof (data));

      std::memcpy(&raw[index], (uint8_t*)&data, sizeof (data));
      this->size = index + sizeof (data);
    }

    template <typename T> T read(uint32_t index) const {
      return *((T*)&raw[index]);
    }

    // TODO: check endianness at compile time rather than runtime
    static bool isMachineBigEndian() {
      uint16_t i = 300;
      if ((*(uint8_t*)&i) != 44)
        return true;

      return false;
    };

    template <typename T> static void swapByteOrder(T* data) {
      if (sizeof (T) < 2)
        return;

      uint8_t* p = (uint8_t*)data;

      for (uint32_t i = 0; i < (sizeof (T) / 2); i++) {
        uint8_t temp = p[sizeof (T) - i - 1];
        std::memcpy(&p[sizeof (T) - i - 1], &p[i], 1);
        std::memcpy(&p[i], &temp, 1);
      }
    }

  public:
    Buffer(uint32_t size = BLOCK_SIZE);
    Buffer(const void* const data, uint32_t size);
    Buffer(const void* const data, uint32_t size, uint32_t index);
    ~Buffer();

    void resize(uint32_t size);
    void clear(uint32_t index = 0);
    void erase(uint32_t length);
    void erase(uint32_t index, uint32_t length);

    void writeInt8(int8_t value);
    void writeInt8(int8_t value, uint32_t index);
    void writeUInt8(uint8_t value);
    void writeUInt8(uint8_t value, uint32_t index);
    void writeInt16BE(int16_t value);
    void writeInt16BE(int16_t value, uint32_t index);
    void writeInt16LE(int16_t value);
    void writeInt16LE(int16_t value, uint32_t index);
    void writeUInt16BE(uint16_t value);
    void writeUInt16BE(uint16_t value, uint32_t index);
    void writeUInt16LE(uint16_t value);
    void writeUInt16LE(uint16_t value, uint32_t index);
    void writeInt32BE(int32_t value);
    void writeInt32BE(int32_t value, uint32_t index);
    void writeInt32LE(int32_t value);
    void writeInt32LE(int32_t value, uint32_t index);
    void writeUInt32BE(uint32_t value);
    void writeUInt32BE(uint32_t value, uint32_t index);
    void writeUInt32LE(uint32_t value);
    void writeUInt32LE(uint32_t value, uint32_t index);
    void writeInt64BE(int64_t value);
    void writeInt64BE(int64_t value, uint32_t index);
    void writeInt64LE(int64_t value);
    void writeInt64LE(int64_t value, uint32_t index);
    void writeUInt64BE(uint64_t value);
    void writeUInt64BE(uint64_t value, uint32_t index);
    void writeUInt64LE(uint64_t value);
    void writeUInt64LE(uint64_t value, uint32_t index);

    void writeFloatBE(float value);
    void writeFloatBE(float value, uint32_t index);
    void writeFloatLE(float value);
    void writeFloatLE(float value, uint32_t index);
    void writeDoubleBE(double value);
    void writeDoubleBE(double value, uint32_t index);
    void writeDoubleLE(double value);
    void writeDoubleLE(double value, uint32_t index);

    void writeString(std::string& str);
    void writeString(const char* const str);
    void writeString(std::string& str, uint32_t index);
    void writeString(const char* const str, uint32_t index);
    void writeBytes(const void* data, uint32_t length);
    void writeBytes(const void* data, uint32_t length, uint32_t index);
    void writeBuffer(Buffer& buffer);
    void writeBuffer(Buffer& buffer, uint32_t index);

    int8_t readInt8(uint32_t index) const;
    uint8_t readUInt8(uint32_t index) const;
    int16_t readInt16BE(uint32_t index) const;
    int16_t readInt16LE(uint32_t index) const;
    uint16_t readUInt16BE(uint32_t index) const;
    uint16_t readUInt16LE(uint32_t index) const;
    int32_t readInt32BE(uint32_t index) const;
    int32_t readInt32LE(uint32_t index) const;
    uint32_t readUInt32BE(uint32_t index) const;
    uint32_t readUInt32LE(uint32_t index) const;
    int64_t readInt64BE(uint32_t index) const;
    int64_t readInt64LE(uint32_t index) const;
    uint64_t readUInt64BE(uint32_t index) const;
    uint64_t readUInt64LE(uint32_t index) const;

    float readFloatBE(uint32_t index) const;
    float readFloatLE(uint32_t index) const;
    double readDoubleBE(uint32_t index) const;
    double readDoubleLE(uint32_t index) const;

    std::string readString(uint32_t index, uint32_t length) const;
    void readBytes(void* buffer, uint32_t length, uint32_t index = 0) const;
    Buffer readBuffer(uint32_t index, uint32_t length) const;

    uint32_t getSize() const {
      return this->size;
    };

    uint32_t getCapacity() const {
      return this->capacity;
    };
};

#endif
