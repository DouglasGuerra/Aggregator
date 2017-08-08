#include <ros/ros.h>

int main(int argc, char ** argv){

	ros::init(argc, argv, "shared_files_node");

	while(ros::ok)
		ros::spinOnce();
}
