#ifndef BUFFER_H_
#define BUFFER_H_

#include <cstdint>
#include <string>
#include <vector>

class Buffer {
  private:
    std::vector<int8_t> raw;

  public:
    Buffer();

    void writeUInt8(uint8_t value);
    void writeUInt8(uint8_t value, uint32_t index);
    void writeUInt16BE(uint16_t value);
    void writeUInt16BE(uint16_t value, uint32_t index);
    void writeUInt16LE(uint16_t value);
    void writeUInt16LE(uint16_t value, uint32_t index);
    void writeString(std::string str);
    void writeString(std::string str, uint32_t length);
    void writeString(std::string str, uint32_t length, uint32_t index);

    uint32_t size() const;
};

#endif
