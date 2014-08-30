#ifndef BUFFER_H_
#define BUFFER_H_

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

class Buffer {
  private:
    std::vector<uint8_t> raw;
    uint32_t position;

    enum Size {
      DEFAULT = 4096
    };

    template <typename T> void append(T data) {
      if (position + sizeof (data) > this->getCapacity())
        this->resize(position + sizeof (data));

      std::memcpy(&raw[this->position], (uint8_t*)&data, sizeof (data));
      this->position += sizeof (data);
    }

    template <typename T> void insert(T data, uint32_t index) {
      if (position + sizeof (data) > this->getCapacity())
        this->resize(position + sizeof (data));

      std::memcpy(&raw[index], (uint8_t*)&data, sizeof (data));
      this->position = index + sizeof (data);
    }

    template <typename T> T read(uint32_t index) const {
      return *((T*)&raw[index]);
    }

    // TODO: check endianness at compile time rather than runtime
    bool isMachineBigEndian() const {
      uint16_t i = 300;
      if ((*(uint8_t*)&i) != 44)
        return true;

      return false;
    };

    template <typename T> void swapByteOrder(T* data, uint32_t length) const {
      if (length < 2)
        return;

      uint8_t* p = (uint8_t*)data;

      for (uint32_t i = 0; i < (length / 2); i++) {
        uint8_t temp = p[length - i - 1];
        std::memcpy(&p[length - i - 1], &p[i], 1);
        std::memcpy(&p[i], &temp, 1);
      }
    }

    void resize(uint32_t size) {
      this->raw.resize(size);
    }

  public:
    Buffer(uint32_t size = Size::DEFAULT);

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

    void writeString(std::string& str);
    void writeString(std::string& str, uint32_t length);
    void writeString(std::string& str, uint32_t length, uint32_t index);
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

    std::string readString(uint32_t index, uint32_t length) const;
    Buffer readBuffer(uint32_t index, uint32_t length) const;

    uint32_t getPosition() const {
      return this->position;
    };

    // purpose of if can change dynamically?
    uint32_t getCapacity() const {
      return this->raw.capacity();
    };
};

#endif
