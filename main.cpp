#include <iostream>

#include "Buffer.h"

using namespace std;

int main() {
  Buffer buffer;

  /*
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
  Buffer b3;
  b3.writeString(s2);
  Buffer b4;
  string s3 = " over there!";
  b4.writeString(s3);
  b3.writeBuffer(b4);
  cout << b3.readString(0, s2.size() + s3.size()) << endl;
  */

  string test = "hello there you";
  buffer.writeString(test);
  cout << buffer.readString(0, 15) << endl;

  buffer.erase(1); // erase the first 6 bytes

  cout << buffer.readString(0, buffer.getSize()) << endl;

  return 0;
}
