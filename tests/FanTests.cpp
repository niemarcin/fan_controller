#define CATCH_CONFIG_MAIN
#include "external/catch.hpp"
#include "Fan.hpp"

TEST_CASE("Fan - setSpeed() behavior", "[Fan]") {
    Fan fan{};

    constexpr auto disabledRpm = Fan::disabledFanRpm;
    constexpr auto minRpm = Fan::minFanRpm;
    constexpr auto maxRpm = Fan::maxFanRpm;

    SECTION("created fan is disabled") {
        CHECK(fan.getSpeed() == disabledRpm);
    }

    SECTION("setting proper values") {
        fan.setSpeed(minRpm);
        CHECK(fan.getSpeed() == minRpm);

        fan.setSpeed(maxRpm);
        CHECK(fan.getSpeed() == maxRpm);

        fan.setSpeed(disabledRpm);
        CHECK(fan.getSpeed() == disabledRpm);
    }

    SECTION("setting invalid values") {
        auto before = fan.getSpeed();

        REQUIRE_THROWS_AS(fan.setSpeed(minRpm - 1), std::invalid_argument);
        CHECK(fan.getSpeed() == before);

        REQUIRE_THROWS_AS(fan.setSpeed(maxRpm + 1), std::invalid_argument);
        CHECK(fan.getSpeed() == before);
    }
}

SCENARIO("Fan - enable() & disable() behavior", "[Fan]") {
    GIVEN("Created fan with previously set initial speed") {
        Fan fan{};
        auto disabledRpm = 0;
        auto initialRpm = 2500;

        fan.setSpeed(initialRpm);
        REQUIRE(fan.getSpeed() == initialRpm);

        WHEN("Fan is disabled") {
            fan.disable();

            THEN("Fan speed equals 0") {
                REQUIRE(fan.getSpeed() == disabledRpm);
            }
        }
    }

    GIVEN("Created and not enabled fan") {
        Fan fan{};
        auto disabledRpm = 0;
        auto enabledRpm = 1000;

        REQUIRE(fan.getSpeed() == disabledRpm);

        WHEN("Fan is enabled") {
            fan.enable();

            THEN("Fan speed equals 1000") {
                REQUIRE(fan.getSpeed() == enabledRpm);
            }
        }
    }
}
