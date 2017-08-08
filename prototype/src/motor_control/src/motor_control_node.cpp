#include <ros/ros.h>
#include <time.h>
#include <iostream>
#include "shared_files/drive.h"
using namespace std;

//Subscriber 
ros::Subscriber drive_sub;

//ROS TIME
double last_write = 0;
double current_time = 0;

//variables for speed and direction
uint32_t speed = 0;
uint32_t direction = 0;

//Writing motor values
void writeValues(){

	//Send to I2C these values
	ROS_INFO("speed: %d", speed);
	ROS_INFO("direction: %d", direction);

	//updating the time I2C was written
	last_write = ros::Time::now().toSec();
}

//Callback function for drive messages
void driveCallback(const shared_files::drive drive_msg){

	//reading in values
	speed = drive_msg.speed;
	direction = drive_msg.direction;

	//calling the write values
	writeValues();
}

int main(int argc, char **argv){

	//initializing the node that defines that will handle motors
	ros::init(argc, argv, "motor_node");

	//Node Handle necessary for ros
	ros::NodeHandle nh;

	//subscriber to drive messages
	drive_sub = nh.subscribe("drive", 1000, driveCallback);

	//main loop for ros
	while(ros::ok()){

		//updating the current time
		current_time = ros::Time::now().toSec();

		//defaulting to zero for motor values
		//write the values only once
		if(current_time - last_write >= 0.500 && direction != 0 && speed != 0){
			direction = 0;
			speed = 0;
			writeValues();

		}
		ros::spinOnce();
	}
}
