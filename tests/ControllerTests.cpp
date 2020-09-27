#include "../external/catch.hpp"
#include "../external/hippomocks.h"
#include "../Controller.hpp"
#include "MockThermometer.hpp"

TEST_CASE("Controller - fan RPM management behavior", "[Controller]") {

    MockThermometer thermometer{};
    Fan fan{};

    constexpr auto disabledRpm = Fan::disabledFanRpm;
    constexpr auto minRpm = Fan::minFanRpm;
    constexpr auto maxRpm = Fan::maxFanRpm;

    constexpr double targetTemperature = 36.6;
    constexpr double tolerance = .5;

    Controller c{thermometer, fan, targetTemperature, tolerance, nullptr};


    SECTION("Fan is disabled after controller is created") {
        CHECK(fan.getSpeed() == disabledRpm);
    }
    
    SECTION("Controller should disable fan when temperature is below threshold") {
        fan.setSpeed(minRpm);
        REQUIRE(fan.getSpeed() == minRpm);

        thermometer.setTemperature(targetTemperature - 2 * tolerance);
        c.updateRpm();

        CHECK(fan.getSpeed() == disabledRpm);
    }
    
    SECTION("Controller should set fan to minimal speed when temperature is in the middle of range <<target +/- tolerance>>") {
        thermometer.setTemperature(targetTemperature);
        c.updateRpm();

        CHECK(fan.getSpeed() == minRpm);
    }

    SECTION("Controller should set fan to minimal speed when temperature is on high end of range <<target +/- tolerance>>") {
        thermometer.setTemperature(targetTemperature + tolerance);
        c.updateRpm();

        CHECK(fan.getSpeed() == minRpm);
    }

    SECTION("Controller should set fan to minimal speed when temperature is on low end of range <<target +/- tolerance>>") {
        thermometer.setTemperature(targetTemperature - tolerance);
        c.updateRpm();

        CHECK(fan.getSpeed() == minRpm);
    }

    SECTION("Controller should increase fan speed when temperature is above threshold") {
        fan.setSpeed(2000);
        int speedIncrease = static_cast<int>(tolerance / temperatureStep);
        int targetSpeed = fan.getSpeed() + speedIncrease;
        targetSpeed = targetSpeed > maxRpm ? maxRpm : targetSpeed;

        thermometer.setTemperature(targetTemperature + 2 * tolerance);
        c.updateRpm();

        CHECK(fan.getSpeed() == targetSpeed);
    }
}
