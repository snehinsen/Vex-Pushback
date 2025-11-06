from vex import *

class Handlers:
    controller: Controller
    brain: Brain
    driveTraint: DriveTrain

    def __init__(self, b: Brain, c: Controller, d: DriveTrain) -> None:
        self.brain = b
        self.controller = c
        self.driveTraint = d

    def test(self):
        self.controller.screen.print("Testing")
        self.brain.screen.print("Testing")