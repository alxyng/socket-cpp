#include <iostream>

#include "Buffer.h"

using namespace std;

int main() {
  Buffer buffer;

  buffer.writeUInt16BE(2109);
  buffer.writeString("hello");

  cout << buffer.readInt8(2) << endl;

  return 0;
}
