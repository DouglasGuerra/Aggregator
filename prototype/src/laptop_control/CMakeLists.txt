cmake_minimum_required(VERSION 2.8.3)
project(laptop_control)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  message_generation
  message_runtime
  roscpp
  rospy
  std_msgs
  shared_files
)

##package for NCurses to read in from keyboard
find_package(PkgConfig REQUIRED)
pkg_check_modules(ncurses++ REQUIRED ncurses++)

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
   LIBRARIES laptop_control
   CATKIN_DEPENDS genmsg message_generation message_runtime roscpp rospy std_msgs shared_files
   DEPENDS system_lib
)

###############
##Executables##
###############

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(laptop_node src/laptop_node.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
#add_dependencies(laptop_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(laptop_node ${catkin_LIBRARIES} ncurses)
