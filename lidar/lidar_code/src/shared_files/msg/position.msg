# The values represent if we are to the left, right, or center in the arena
# 
# Found tells us if we have found our object, if not we need to rotate
# 	1 = found object, so read position and direction variables to know if we need to move
#	0 = not found object so rotate robot either clockwise or counter-clockwise
#
# Position tells us where we are => left, right or center of the arena
#	-1 = left
#	0 = center
#	1 = right
#
# Direction tells us which direction we need to move => left or right
#	-1 = left
#	0 = stop moving and go forward, we are too close to the dump_site and we don't want to hit
#	1 = right
#
# Rotation_enable tells us if we are centered and need to begin worrying about rotation
#	1 = centered, we need to orient ourselves
#	0 = not centered, don't worry about rotation
#
# Rotation_direction tells us the direction we need to rotate 
#	-1 = counter-clockwise
#	0 = parallel to collecto bin, don't need to rotate anymore
#	1 = clockwise
#
# angle represents the angle deviation from being in parallel to the collector bin

int8 found
int8 position
int8 direction
int8 rotation_enable
int8 rotation_direction
float32 angle
