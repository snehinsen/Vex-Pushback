#include "handlers.h"

// Constructor
Handlers::Handlers() {
  // Leave empty unless you are initializing stuff
}

// --------------------------
// Generic
// --------------------------

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

// --------------------------
// Generic motor handler
// --------------------------

void Handlers::spinMotor(vex::motor& m, double speedPct) {
  if (fabs(speedPct) < 1) {
    m.stop(vex::brakeType::coast);
    return;
  }

  if (speedPct > 0) {
    m.spin(vex::directionType::fwd, speedPct, vex::percentUnits::pct);
  } else {
    m.spin(vex::directionType::rev, -speedPct, vex::percentUnits::pct);
  }
}
