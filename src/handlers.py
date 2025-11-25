from vex import *
from definitions import brain, controller, driveTrain, belt, intake_flywheel

class Handlers:
    def __init__(self):
        # No need to pass anything in — we imported directly.
        self.brain = brain
        self.controller = controller
        self.driveTrain = driveTrain
        self.belt = belt
        self.intake = intake_flywheel

    # -----------------------
    # Generic Test function
    # -----------------------
    def test(self):
        self.controller.screen.print("Testing")
        self.brain.screen.print("Testing")

    # -----------------------
    # INTAKE EVENTS
    # -----------------------
    def intake_forward(self):
        self.intake.set_velocity(100, PERCENT)
        self.intake.spin(FORWARD)

    def intake_reverse(self):
        self.intake.set_velocity(100, PERCENT)
        self.intake.spin(REVERSE)

    def intake_stop(self):
        self.intake.stop()

    # -----------------------
    # BELT EVENTS
    # -----------------------
    def belt_forward(self):
        self.belt.set_velocity(80, PERCENT)
        self.belt.spin(FORWARD)

    def belt_reverse(self):
        self.belt.set_velocity(80, PERCENT)
        self.belt.spin(REVERSE)

    def belt_stop(self):
        self.belt.stop()
