#include "handlers.h"

// Constructor
Handlers::Handlers() {
    // Nothing to do — devices already exist globally in definitions.cpp
}

// Test function
void Handlers::test() {
    Controller1.Screen.print("Testing");
    Brain.Screen.print("Testing");
}

// --------------------------
// Intake controls
// --------------------------

void Handlers::intake_forward() {
    intake_flywheel.setVelocity(100, vex::percentUnits::pct);
    intake_flywheel.spin(vex::directionType::fwd);
}

void Handlers::intake_reverse() {
    intake_flywheel.setVelocity(100, vex::percentUnits::pct);
    intake_flywheel.spin(vex::directionType::rev);
}

void Handlers::intake_stop() {
    intake_flywheel.stop();
}

// --------------------------
// Belt controls
// --------------------------

void Handlers::belt_forward() {
    belt.setVelocity(80, vex::percentUnits::pct);
    belt.spin(vex::directionType::fwd);
}

void Handlers::belt_reverse() {
    belt.setVelocity(80, vex::percentUnits::pct);
    belt.spin(vex::directionType::rev);
}

void Handlers::belt_stop() {
    belt.stop();
}
