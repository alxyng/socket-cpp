#include <iostream>

#include "Buffer.h"

using namespace std;

int main() {
  Buffer b;
  b.writeUInt32BE(70);

  //cout << b.readInt8(3) << endl;

  Buffer b2 = b.readBuffer(0, 4);

  cout << b2.readString(3, 1) << endl;

  return 0;
}
