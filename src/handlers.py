from vex import *

class Handlers:
    controller: Controller
    brain: Brain

    def __init__(self, b: Brain, c: Controller) -> None:
        self.brain = b
        self.controller = c

    def test(self):
        self.controller.screen.print("Testing")