#include <iostream>
#include <exception>
#include <unistd.h>

#include "include/Address.hpp"
#include "include/Buffer.hpp"
#include "include/IPAddress.hpp"
#include "include/Socket.hpp"
#include "include/Utils.hpp"

using namespace std;

int main(int argc, const char** argv) {
    if (argc < 2) {
        cout << "Usage: ./main server/client" << endl;
        exit(0);
    }

    if (strcmp(argv[1], "server") == 0) {
        Socket socket;
        try {
            socket.connect(Address("192.168.1.1", 21099));
        } catch (exception& e) {
            cout << "Couldn't connect homie" << endl;
        }
    } else if (strcmp(argv[1], "client") == 0) {
        //
    } else {
        cout << "Invalid option" << endl;
        exit(0);
    }

    return 0;
}
