#include <iostream>
#include <fstream>

#include "Buffer.h"

using namespace std;

int main() {
  ifstream s("example.dat", ios::binary);
  if (s) {
    s.seekg(0, s.end);
    int length = s.tellg();
    cout << length << endl;
    s.seekg(0, s.beg);

    char* data = new char[length];
    s.read(data, length);

    Buffer b(data, length);

    cout << (uint32_t)b.readUInt8(3) << endl;
  } else {
    cout << "Couldn't open file" << endl;
  }

  return 0;
}
