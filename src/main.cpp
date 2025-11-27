/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       s300107930                                                */
/*    Created:      11/26/2025, 2:16:57 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "definitions.h"
#include "handlers.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Python → C++ translated state
bool remote_control_code_enabled = true;
bool drivetrain_stopped = false;

// Drive state (ramped tank control)
double left_current_speed  = 0;
double right_current_speed = 0;
constexpr double drive_ramp_factor = 0.2;

// Handler instance
Handlers handlers;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------*/
/* Python: ramp_speed()                        */
/*---------------------------------------------*/
double ramp_speed(double current, double target) {
  return current + (target - current) * drive_ramp_factor;
}

/*---------------------------------------------*/
/* Python rc_auto_loop_function_controller()    */
/*---------------------------------------------*/
int rc_drive_task() {
  while (true) {

    if (!remote_control_code_enabled) {
      wait(20, msec);
      continue;
    }

    // Arcade drive inputs
    double forward = Controller1.Axis3.position();
    double turn    = Controller1.Axis2.position();   // ← turn stick

    double left_target  = forward + turn;
    double right_target = forward - turn;

    left_current_speed  = ramp_speed(left_current_speed, left_target);
    right_current_speed = ramp_speed(right_current_speed, right_target);

    // Deadband
    if (fabs(forward) < 5 && fabs(turn) < 5) {
      if (!drivetrain_stopped) {
        left_drive.stop();
        right_drive.stop();
        drivetrain_stopped = true;
      }
    } else {
      drivetrain_stopped = false;

      left_drive.setVelocity(left_current_speed, percentUnits::pct);
      right_drive.setVelocity(right_current_speed, percentUnits::pct);

      left_drive.spin(directionType::fwd);
      right_drive.spin(directionType::fwd);
    }

    wait(20, msec);
  }

  return 0;
}

/*---------------------------------------------*/
/* Python mechanism_idle_loop()                */
/*---------------------------------------------*/
int mechanism_idle_task() {
  while (true) {
    // Intake stop when L1/L2 are NOT pressed
    if (!(Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing())) {
      handlers.intake_stop();
    }

    // Belt stop when R1/R2 are NOT pressed
    if (!(Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing())) {
      handlers.belt_stop();
    }

    wait(20, msec);
  }

  return 0;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // Python: brain.screen.print("Driver control active")
  Brain.Screen.clearScreen();
  Brain.Screen.print("Driver control active");

  // ============================
  // Register button events
  // ============================

  // Intake (L1/L2)
  Controller1.ButtonL1.pressed([](){ handlers.intake_forward(); });
  Controller1.ButtonL2.pressed([](){ handlers.intake_reverse(); });

  // Belt (R1/R2)
  Controller1.ButtonR1.pressed([](){ handlers.belt_forward(); });
  Controller1.ButtonR2.pressed([](){ handlers.belt_reverse(); });

  // Test button (A)
  Controller1.ButtonA.pressed([](){ handlers.test(); });

  // ============================
  // Background threads
  // ============================
  thread driveThread(rc_drive_task);
  thread mechThread(mechanism_idle_task);

  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
