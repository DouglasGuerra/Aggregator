# These value are sent when the robot is already centered, and we need to orient the robot to
# have it parallel to the dump site
#
# Enable tells us if we have finished centering the robot and we can worry about rotation
#
# Direction tells us whether to rotate clockwise or counter-clockwise
#	-1 = counter-clockwise
#	1 = clockwise
#	0 = in parallel, no need to rotate
#
# Angle represents, in degrees, how much we need to rotate to be in parallel to the dump site

int8 enable
int8 direction 	
float32 angle
