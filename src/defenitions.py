from vex import *

left_drive = Motor(Ports.PORT18, GearSetting.RATIO_18_1, False)
right_drive = Motor(Ports.PORT19, GearSetting.RATIO_18_1, False)
driveTrain=DriveTrain(left_drive, right_drive)

belt = Motor(Ports.PORT3, GearSetting.RATIO_18_1, False)
intake_flywheel = Motor(Ports.PORT2, GearSetting.RATIO_18_1, False)