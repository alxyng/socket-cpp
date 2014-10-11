#ifndef ADDRESS_HPP_
#define ADDRESS_HPP_

#include "IPAddress.hpp"

#include <cstdint>

class Address {
private:
	IPAddress* ip;
	uint16_t port;

public:
	Address(IPAddress ip, uint16_t port);
	std::string getIP() const;
	uint16_t getPort() const;
};

#endif
