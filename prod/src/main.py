from vex import *
from handlers import Handlers
from definitions import *

handlers = Handlers()

remote_control_code_enabled = True
drivetrain_stopped = False

# --------------------------------
# TANK DRIVE LOOP (unchanged)
# --------------------------------
left_current_speed = 0
right_current_speed = 0
drive_ramp_factor = 0.2

def ramp_speed(current, target):
    return current + (target - current) * drive_ramp_factor

def rc_auto_loop_function_controller():
    global drivetrain_stopped
    global left_current_speed, right_current_speed

    while True:
        if not remote_control_code_enabled:
            wait(20, MSEC)
            continue

        left_target = controller.axis3.position()
        right_target = controller.axis2.position()

        left_current_speed = ramp_speed(left_current_speed, left_target)
        right_current_speed = ramp_speed(right_current_speed, right_target)

        if abs(left_target) < 5 and abs(right_target) < 5:
            if not drivetrain_stopped:
                left_drive.stop()
                right_drive.stop()
                drivetrain_stopped = True
        else:
            drivetrain_stopped = False
            left_drive.set_velocity(left_current_speed, PERCENT)
            right_drive.set_velocity(right_current_speed, PERCENT)
            left_drive.spin(FORWARD)
            right_drive.spin(FORWARD)

        wait(20, MSEC)


# --------------------------------
# NON-DRIVETRAIN MECHANISM LOOP
# (just checks when buttons are released)
# --------------------------------
def mechanism_idle_loop():
    while True:
        # INT intake stop
        if not (controller.buttonL1.pressing() or controller.buttonL2.pressing()):
            handlers.intake_stop()

        # BELT stop
        if not (controller.buttonR1.pressing() or controller.buttonR2.pressing()):
            handlers.belt_stop()

        wait(20, MSEC)


# --------------------------------
# DRIVER CONTROL
# --------------------------------
def user_control():
    brain.screen.clear_screen()
    brain.screen.print("Driver control active")

    # ============================
    # Register events (handlers.py)
    # ============================

    # Intake (L1/L2)
    controller.buttonL1.pressed(handlers.intake_forward)
    controller.buttonL2.pressed(handlers.intake_reverse)

    # Belt (R1/R2)
    controller.buttonR1.pressed(handlers.belt_forward)
    controller.buttonR2.pressed(handlers.belt_reverse)

    # Test button (A)
    controller.buttonA.pressed(handlers.test)

    # Start loops
    Thread(rc_auto_loop_function_controller)
    Thread(mechanism_idle_loop)

    while True:
        wait(20, MSEC)


# --------------------------------
# MAIN
# --------------------------------
def main():
    comp = Competition(user_control, lambda: None)
    print(comp)

if __name__ == "__main__":
    main()
