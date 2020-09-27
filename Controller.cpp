#include "Controller.hpp"

Controller::Controller(const IThermometer& thermometer, Fan& fan, 
                       const double targetTemp, const double tolerance, 
                       const std::shared_ptr<LcdDisplay>& lcd)
    :thermometer_(thermometer)
    ,fan_(fan)
    ,targetTemp_(targetTemp)
    ,tolerance_(tolerance)
    ,lcd_(lcd)
{
}

void Controller::updateRpm() {
    double currentTemp = thermometer_.getTemperature();
    if (isTemperatureBelowThreshold(currentTemp)) {
        fan_.disable();
    }
    else if (isTemperatureAboveThreshold(currentTemp)) {
        int speedIncrease = static_cast<int>((currentTemp - (targetTemp_ + tolerance_)) / temperatureStep);
        int newSpeed = fan_.getSpeed() + speedIncrease;
        newSpeed = newSpeed > Fan::maxFanRpm ? Fan::maxFanRpm : newSpeed;
        while (fan_.getSpeed() < newSpeed) {
            fan_.setSpeed(newSpeed);
        }
    }
    else {
        fan_.setSpeed(Fan::minFanRpm);
    }
}

void Controller::displayInfo() const {}

bool Controller::isTemperatureBelowThreshold(double temperature) {
    return temperature < targetTemp_ - tolerance_;
}

bool Controller::isTemperatureAboveThreshold(double temperature) {
    return temperature > targetTemp_ + tolerance_;
}
