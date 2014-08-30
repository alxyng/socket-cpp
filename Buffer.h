#ifndef BUFFER_H_
#define BUFFER_H_

#include <arpa/inet.h>
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
      std::memcpy(&raw[this->position], (uint8_t*)&data, sizeof (data));
      this->position += sizeof (data);
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
        memcpy(&p[length - i - 1], &p[i], 1);
        memcpy(&p[i], &temp, 1);
      }
    }

  public:
    Buffer(uint32_t size = Size::DEFAULT);

    void writeUInt8(uint8_t value);
    void writeUInt8(uint8_t value, uint32_t index);
    void writeUInt16BE(uint16_t value);
    void writeUInt16BE(uint16_t value, uint32_t index);
    void writeUInt16LE(uint16_t value);
    void writeUInt16LE(uint16_t value, uint32_t index);
    void writeString(std::string& str);
    void writeString(std::string& str, uint32_t length);
    void writeString(std::string& str, uint32_t length, uint32_t index);
    void writeBuffer(Buffer& buffer);
    void writeBuffer(Buffer& buffer, uint32_t index);

    uint8_t readUInt8(uint32_t index) const;
    uint16_t readUInt16BE(uint32_t index) const;
    uint16_t readUInt16LE(uint32_t index) const;
    std::string readString(uint32_t index, uint32_t length) const;
    Buffer readBuffer(uint32_t index, uint32_t length) const;

    uint32_t size() const {
      return this->raw.size();
    };
};

#endif
