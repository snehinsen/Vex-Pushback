from vex import MotorGroup, Motor

class TwoWheelDriveTrain():
    motor1: Motor
    motor2: Motor
    mGroup: MotorGroup

    def __init__(self, m1, m2) -> None:
        self.motor1 = m1
        self.motor2 = m2

        self.mGroup = MotorGroup(self.motor1, self.motor2)

        
    

class FourWheelDriveTrain():
    pass