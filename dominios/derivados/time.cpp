#include "time.hpp"

void Time::validate(std::string time) {
    if (std::stoi(time) < 1 || std::stoi(time) > 365) {
        throw std::invalid_argument("Invalid time");
    }
}