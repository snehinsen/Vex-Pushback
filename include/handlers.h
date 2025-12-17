#pragma once
#include "vex.h"
#include "definitions.h"

class Handlers {
public:
    Handlers();

    // Generic
    void test();

    // Intake events
    void intake_forward();
    void intake_reverse();
    void intake_stop();

    // Belt events
    void belt_forward();
    void belt_reverse();
    void belt_stop();
    void spinMotor(vex::motor & m, double speedPct);
};
