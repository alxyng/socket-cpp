#include <iostream>

#include "Buffer.h"

using namespace std;

int main() {
  Buffer buffer;

  buffer.writeUInt16BE(2109);

  std::string str = "bonjour";

  buffer.writeString(str);

  cout << buffer.readInt8(5) << endl;

  buffer.writeInt8('e', 5);

  cout << buffer.readString(2, 4) << endl;

  return 0;
}
