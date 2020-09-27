#pragma once

class Fan {
public:
    void setSpeed(const int newRpm);
    int getSpeed() const;
    bool disable();
    bool enable();

private:
    int rpm{0};
};
