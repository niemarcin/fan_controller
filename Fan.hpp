#pragma once

class Fan {
public:
    static const int disabledFanRpm{0};
    static const int minFanRpm{1000};
    static const int maxFanRpm{3000};

    void setSpeed(const int newRpm);
    int getSpeed() const;
    bool disable();
    bool enable();

private:
    int rpm{0};
};
