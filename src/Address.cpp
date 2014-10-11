#include "Address.hpp"

#include "IPAddress.hpp"

#include <cstdint>
#include <string>

Address::Address(IPAddress ip, uint16_t port) {
	this->ip = &ip;
	this->port = port;
}

std::string Address::getIP() const {
	return std::string("127.0.0.1");
}

uint16_t Address::getPort() const {
	return this->port;
}
