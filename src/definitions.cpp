#include "definitions.h"

// Brain & controller
vex::brain Brain;
vex::controller Controller1(vex::controllerType::primary);

// Drive motors
vex::motor left_drive(vex::PORT18, vex::gearSetting::ratio18_1, false);
vex::motor right_drive(vex::PORT19, vex::gearSetting::ratio18_1, true);

// Drivetrain
vex::drivetrain driveTrain(
    left_drive,
    right_drive,
    319.19,  // wheel travel mm
    295,     // track width mm
    40,      // wheelbase mm
    vex::distanceUnits::mm,
    1.0      // external gear ratio
);

// Other motors
vex::motor belt(vex::PORT3, vex::gearSetting::ratio18_1, false);
vex::motor intake_flywheel(vex::PORT2, vex::gearSetting::ratio18_1, false);

// Sensor
vex::bumper Bumper(Brain.ThreeWirePort.H);
