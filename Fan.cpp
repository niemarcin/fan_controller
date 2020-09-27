#include "Fan.hpp"
#include <stdexcept>
#include <cmath>

void Fan::setSpeed(const int newRpm) {
    if ((newRpm < minFanRpm and newRpm != 0) or newRpm > maxFanRpm) {
        throw std::invalid_argument("Invalid speed");
    }
    auto difference = std::abs(newRpm - rpm);
    for (auto i = 0; i < difference; ++i) {
        if (newRpm > rpm) {
            rpm++;
        } else {
            rpm--;
        }
    }
}

int Fan::getSpeed() const {
    return rpm;
}

bool Fan::disable() {
    rpm = disabledFanRpm;
    return true;
}

bool Fan::enable() {
    rpm = minFanRpm;
    return true;
}
