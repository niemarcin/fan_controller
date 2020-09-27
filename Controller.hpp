#pragma once
#include "IThermometer.hpp"
#include "Fan.hpp"
#include <memory>

constexpr double temperatureStep{0.001};

class LcdDisplay;

class Controller {
public:
    Controller(const IThermometer& thermometer, Fan& fan, 
               const double targetTemp, const double tolerance, 
               const std::shared_ptr<LcdDisplay>& lcd);
    void updateRpm();
    void displayInfo() const;

private:
    const IThermometer& thermometer_;
    Fan& fan_;
    std::shared_ptr<LcdDisplay> lcd_;
    double targetTemp_;
    double tolerance_;

    bool isTemperatureBelowThreshold(double temperature);
    bool isTemperatureAboveThreshold(double temperature);
};
