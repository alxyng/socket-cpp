#include <iostream>

#include "Buffer.h"

using namespace std;

int main() {
  Buffer buffer;

  buffer.writeString("example string");

  uint8_t* data = new uint8_t[4];
  buffer.readBytes(data, 1);

  Buffer b2(data, 4);

  cout << b2.readUInt32LE(0) << endl;
}
