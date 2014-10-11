#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include "Address.hpp"
#include "Buffer.hpp"

#include <cstdint>
#include <exception>
#include <netdb.h>
#include <netinet/in.h>
#include <string>

class Socket {
private:
	int type;
	int state;
	struct addrinfo hints;

	int fd;

	enum TYPE {
		TCP,
		UDP,
		RAW
	};

	enum STATE {
		DISCONNECTED,
		CONNECTED
	};

	enum CLOSE {
		NO_RECEIVE,
		NO_TRANSMIT,
		BOTH
	};

	static const int RECEIVE_SIZE = 4096;

	void* getInternetAddress(struct sockaddr *sa);

public:
	Socket(int type = TYPE::TCP);
	~Socket();

	// Client
	void connect(Address addr);

	// Server
	void bind(Address addr);
	void listen(int n);
	void accept();

	bool close(const int how = CLOSE::BOTH);

	void setBlocking(bool blocking);
	void setReceiveTimeout(float timeout);

	bool send(Buffer buffer);
	Buffer receive();

	int getFileDescriptor() const;

	explicit operator bool() const;
};

#endif
