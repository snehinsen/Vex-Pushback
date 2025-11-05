from vex import *
from handlers import Handlers
from defenitions import *

brain = Brain()
controller = Controller()
handlers = Handlers(brain, controller)

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here

def user_control():
    brain.screen.clear_screen()
    brain.screen.print("driver control")
    # place driver control in this while loop

    belt.set_velocity(50, PERCENT)
    belt.set_stopping(HOLD)
    while True:
        Controller.buttonA.pressed(handlers.test)

# create competition instance
comp = Competition(user_control, autonomous)


