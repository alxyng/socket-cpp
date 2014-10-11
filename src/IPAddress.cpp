#include "IPAddress.hpp"

#include <stdlib.h>
#include <string>

#include <iostream>

IPAddress::IPAddress(std::string ip) {
	std::string delimiter = ".";
	std::string token;
	size_t position;

	bool last = false;
	for (int i = 4; i > 0; i--) {
		if (last)
			break;

		position = ip.find(".");
		if (position == std::string::npos)
			last = true;

		token = ip.substr(0, position);

		uint8_t byte; // convert the token to uint8_t
		byte << (i - 1) * 8;
		this->raw |= byte;

		ip.erase(0, position + delimiter.length());
	}
}

IPAddress::IPAddress(const char* ip) {
	IPAddress(std::string(ip));
}

/*

192.168.1.1





*/
