cmake_minimum_required(VERSION 2.8.3)
project(filtering)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  laser_geometry
  pcl_conversions
  pcl_ros
  roscpp
  sensor_msgs
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
  LIBRARIES filtering
  CATKIN_DEPENDS laser_geometry pcl_conversions pcl_ros roscpp sensor_msgs
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

#executable for input node from laser scan
add_executable(convert_input_cloud_node src/convert_input_cloud.cpp)
target_link_libraries(convert_input_cloud_node ${catkin_LIBRARIES})

#adding executables for pass through filter node
add_executable(passthrough_filter_node src/passthrough_filter.cpp)
target_link_libraries(passthrough_filter_node ${catkin_LIBRARIES})

#executable for statistical outlier filter node
add_executable(statistical_outlier_filter_node src/statistical_outlier_filter.cpp)
target_link_libraries(statistical_outlier_filter_node ${catkin_LIBRARIES})
