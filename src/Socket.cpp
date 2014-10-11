#include "Socket.hpp"

#include "Buffer.hpp"
#include "Utils.hpp"

#include <arpa/inet.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

Socket::Socket(int type) {
	this->type = type;
	this->state = STATE::DISCONNECTED;

	struct addrinfo hints;
	std::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // IPv4 or IPv6

	switch (type) {
		case TYPE::UDP:
			hints.ai_socktype = SOCK_DGRAM;
			break;
		case TYPE::RAW:
			hints.ai_socktype = SOCK_RAW;
			break;
		default:
			hints.ai_socktype = SOCK_STREAM;
			break;
	}

	this->hints = hints;
}

Socket::~Socket() {
	this->close();
}

void Socket::connect(Address addr) {
	int rv;
	struct addrinfo *servinfo;
	if ((rv = getaddrinfo(addr.getIP().c_str(), Utils::toString(addr.getPort()).c_str(), &this->hints, &servinfo)) != 0) {
		//fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return;
	}

	// loop through all the results and connect to the first we can
	struct addrinfo *p;
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((this->fd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			//perror("client: socket");
			continue;
		}

		if (::connect(this->fd, p->ai_addr, p->ai_addrlen) == -1) {
			::close(this->fd);
			//perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		//fprintf(stderr, "client: failed to connect\n");
		//return 2;
		return;
	} else {
		this->state = STATE::CONNECTED;
	}

	char s[INET6_ADDRSTRLEN];
	inet_ntop(p->ai_family, this->getInternetAddress((struct sockaddr *)p->ai_addr), s, sizeof s);
	//printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure
}

bool Socket::close(const int how) {
	return shutdown(this->fd, how) == 0;
}

void Socket::setBlocking(bool blocking) {
	int status = fcntl(this->fd, F_GETFL);

	if (blocking)
		fcntl(this->fd, F_SETFL, status & ~O_NONBLOCK);
	else
		fcntl(this->fd, F_SETFL, status | O_NONBLOCK);
}

void Socket::setReceiveTimeout(float timeout) {
	struct timeval tv;

	tv.tv_sec = (int)timeout;  /* 30 Secs Timeout */
	tv.tv_usec = (timeout - (int)timeout) * 1000000;  // Not init'ing this can cause strange errors

	setsockopt(this->fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval));
}

bool Socket::send(Buffer buffer) {
	const int totalBytes = buffer.getSize();
	int bytesSent = 0;
	int n;

	uint8_t* data = new uint8_t[totalBytes];
	buffer.readBytes(data, totalBytes, 0);

	while (bytesSent < totalBytes) {
		n = ::send(this->fd, data, totalBytes - bytesSent, 0);
		if (n == -1)
			break; // throw maybe?

		bytesSent += n;
	}

	delete [] data;

	return n > -1;
}

Buffer Socket::receive() {
	int n;
	uint8_t data[RECEIVE_SIZE];

	n = recv(this->fd, data, RECEIVE_SIZE, 0);
	if (n == -1) {
		// didnt work - throw maybe?? auto return for -1 or buffer??
	}

	return Buffer(data, n);
}

int Socket::getFileDescriptor() const {
	return this->fd;
}

// get sockaddr, IPv4 or IPv6:
void* Socket::getInternetAddress(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

Socket::operator bool() const {
	return this->state > STATE::DISCONNECTED;
}
