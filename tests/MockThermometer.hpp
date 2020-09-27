#pragma once

#include "../IThermometer.hpp"

class MockThermometer : public IThermometer {
public:
    double getTemperature() const override {
        return temperature_;
    }

    void setTemperature(double temp) {
        temperature_ = temp;
    }

private:
    double temperature_{0};
};
