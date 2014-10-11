#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <ctime>
#include <string>
#include <sstream>
#include <sys/time.h>

class Utils {
    public:
        template <typename T> static std::string toString(T n) {
            std::stringstream ss;
            ss << n;
            return ss.str();
        }
};

#endif
