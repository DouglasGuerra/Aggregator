cmake_minimum_required(VERSION 2.8.3)
project(pcl_extraction)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  genmsg
  laser_geometry
  pcl_conversions
  pcl_ros
  roscpp
  rospy
  sensor_msgs
  std_msgs
  shared_files
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES pcl_extraction
  CATKIN_DEPENDS std_msgs laser_geometry pcl_conversions pcl_ros roscpp rospy sensor_msgs shared_files
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

#executable for the ransac line model extraction
add_executable(ransac_node src/ransac_node.cpp)
target_link_libraries(ransac_node ${catkin_LIBRARIES})

#executable for the extract indices node
add_executable(extract_indices_node src/extract_indices_node.cpp)
target_link_libraries(extract_indices_node ${catkin_LIBRARIES})

#executable for the centroid (calc_centroid_node.cpp)
add_executable(calc_centroid_node src/calc_centroid_node.cpp)
target_link_libraries(calc_centroid_node ${catkin_LIBRARIES})

#executable for the calc_position_node
add_executable(calc_position_node src/calc_position.cpp)
add_dependencies(calc_position_node calc_position_generate_messages_cpp)
target_link_libraries(calc_position_node ${catkin_LIBRARIES})
