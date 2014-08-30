#include <iostream>

#include "Buffer.h"

using namespace std;

int main() {
  Buffer buffer;

  buffer.writeUInt16LE(2109);

  cout << buffer.readUInt16LE(0) << endl;

  return 0;
}
