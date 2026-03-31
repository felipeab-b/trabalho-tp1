#include "time.hpp"

void Time::validate(int time) {
    if (time < 1 || time > 365) {
        throw invalid_argument("Invalid time");
    }
}

int Time::get() {
    return time;
}

void Time::set(int time) {
    validate(time);
    this->time = time;
}

