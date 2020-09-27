#pragma once

#include "../IThermometer.hpp"

class SlowThermometer : public IThermometer {
public:
    double getTemperature() const override;
};
