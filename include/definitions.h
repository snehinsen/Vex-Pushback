// definitions.h
#pragma once
#include "vex.h"

// Brain & Controller
extern vex::brain Brain;
extern vex::controller Controller1;

// Drive motors
extern vex::motor left_drive;
extern vex::motor right_drive;

// Drivetrain
extern vex::drivetrain driveTrain;

// Other motors
extern vex::motor belt;
extern vex::motor intake_flywheel;

// Sensor
extern vex::bumper bumper;
