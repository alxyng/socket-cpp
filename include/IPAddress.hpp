#ifndef IPADDRESS_HPP_
#define IPADDRESS_HPP_

#include <string>

/**
 * Models both a IPv4.
 */
class IPAddress {
private:
	uint32_t raw;

public:
	IPAddress(std::string ip);
	IPAddress(const char* ip);
};

#endif
