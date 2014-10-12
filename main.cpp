#include <iostream>
#include <exception>
#include <unistd.h>

#include "include/Address.hpp"
#include "include/Buffer.hpp"
#include "include/IPAddress.hpp"
#include "include/Socket.hpp"
#include "include/Utils.hpp"

using namespace std;

void server();
void client();

int main(int argc, const char** argv) {
    if (argc < 2) {
        cout << "Usage: ./main server/client" << endl;
        exit(0);
    }

    if (strcmp(argv[1], "server") == 0) {
        server();
    } else if (strcmp(argv[1], "client") == 0) {
        client();
    } else {
        cout << "Invalid option. Usage: ./main server/client" << endl;
        exit(0);
    }

    return 0;
}

void server() {
    /*
    Socket socket;
    socket.bind(Address("127.0.0.1", 21099));
    socket.listen(10);

    while (true) {
        Socket conn = socket.accept();
    }
    */
}

void client() {
    Socket socket;
    try {
        socket.connect(Address("192.168.1.1", 21099));
    } catch (exception& e) {
        cout << "Couldn't connect homie" << endl;
    }
}
