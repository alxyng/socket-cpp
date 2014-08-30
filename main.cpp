#include <iostream>

#include "Buffer.h"

using namespace std;

int main() {
  Buffer buffer;

  buffer.writeUInt32BE(123);

  cout << buffer.readInt8(3) << endl;

  return 0;
}
