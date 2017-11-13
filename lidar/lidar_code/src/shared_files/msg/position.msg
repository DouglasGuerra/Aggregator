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

int8 found
int8 position
int8 direction
