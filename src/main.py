from vex import *
from handlers import Handlers
from defenitions import *

brain = Brain()
controller = Controller(PRIMARY)
handlers = Handlers(brain, controller)

remote_control_code_enabled = True
drivetrain_stopped = False

def rc_auto_loop_function_controller():
    global drivetrain_stopped
    while True:
        if not remote_control_code_enabled:
            wait(20, MSEC)
            continue

        # Calculate drivetrain speeds
        left_speed = controller.axis3.position() + controller.axis4.position()
        right_speed = controller.axis3.position() - controller.axis4.position()

        # Deadband check
        if abs(left_speed) < 5 and abs(right_speed) < 5:
            if not drivetrain_stopped:
                left_drive.stop()
                right_drive.stop()
                drivetrain_stopped = True
        else:
            drivetrain_stopped = False
            left_drive.set_velocity(left_speed, PERCENT)
            right_drive.set_velocity(right_speed, PERCENT)
            left_drive.spin(FORWARD)
            right_drive.spin(FORWARD)

        wait(20, MSEC)

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("Autonomous code here")

def user_control():
    brain.screen.clear_screen()
    brain.screen.print("Driver control active")

    belt.set_velocity(50, PERCENT)
    belt.set_stopping(HOLD)

    controller.buttonA.pressed(handlers.test)

    while True:
        wait(20, MSEC)

# Competition setup
comp = Competition(user_control, autonomous)
