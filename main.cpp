#include <iostream>

#include "Buffer.h"

using namespace std;

int main() {
  Buffer buffer;

  const char* str = "hello there sir";

  string s = "why ";

  buffer.writeString(s);

  buffer.writeBytes(str, strlen(str), 100);

  cout << buffer.readString(106, 15) << endl;

  string s2 = "what the jefferson is that";

  buffer.writeString(s2, 37);

  buffer.writeInt32BE(1234567890);

  char* juicebox = new char[10];
  juicebox[9] = '\0';

  buffer.readBytes(juicebox, 9, 46);

  cout << "My name is " << juicebox << "!" << endl;

  delete [] juicebox;

  Buffer b2(str, 4);

  cout << b2.readString(0, 4) << endl;

  return 0;
}
