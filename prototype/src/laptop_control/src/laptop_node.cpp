#include <ros/ros.h>
#include <iostream>
#include <ncurses.h>
#include "shared_files/drive.h"
using namespace std;

//Publishing topic for driving
ros::Publisher drive_pub;

int main(int argc, char **argv){

	//initializing the node that defines the controlling motors with the laptop
	ros::init(argc, argv, "laptop_node");

	//Node handle
	ros::NodeHandle nh;

	//publisher for drive messages
	drive_pub = nh.advertise<shared_files::drive>("drive", 1);

	//enabled motors
	bool motors_enabled = FALSE;

	//variable for the speed values
	int speed = 25;
	float percent = 0.1;
	float max = 255.0;

	//variable to hold the value read in
	int in = 0;

	//variable to hold the direction traveling
	int direction = 0;

	//initiallizing ncurses
	initscr();
	keypad(stdscr, TRUE);
	noecho();

	//main loop for ROS when it operates
	while(ros::ok()){

		in = getch();	//taking in input from the keyboard

		if(in == 32 && motors_enabled == FALSE){

			printw("Motors Enabled\n");
			printw("Speed is defaulted to 10%% of the max\n");
			speed = 25;
			direction = 0;
			motors_enabled = TRUE;
		}

		else if(motors_enabled == TRUE){

			//directions
			if(in == KEY_UP){
				printw("FORWARD\n");
				direction = 1;
			}
			else if(in == KEY_DOWN){
				printw("BACKWARD\n");
				direction = 2;
			}
			else if(in == KEY_RIGHT){
				printw("RIGHT\n");
				direction = 3;
			}
			else if(in == KEY_LEFT){
				printw("LEFT\n");
				direction = 4;
			}

			//speeds
			if(in == 43){
				if(percent < 1.0){
					percent += 0.05;
					speed = percent*max;
					printw("Increasing speed by 5%, speed is now %f%% of max\n", percent*100);
				}
				/*if(speed < max){
					speed = speed + 5;
					percent = speed/max;
				*///}
			}
			else if(in == 45){
				if(percent > 0.1){
					percent -= 0.05;
					speed = percent*max;
					printw("Decreasing speed by 5%, speed is now %f%% of max\n", percent*100);

				}
				/*if(speed > 0){
					speed = speed - 5;
					percent = speed/max;
					printw("Increasing speed by 5%, speed is now %f%% of max\n", percent);
				*///}
			}

			//turning off motors
			if(in == ' '){
				printw("Disabling Motors\n");
				printw("Press q to exit the program\n");
				motors_enabled = FALSE;
				clear();
			}

			refresh();	//for ncurses.h
		}

		//publishing to drive msgs if motors are enables
		if(motors_enabled){
			shared_files::drive drive_msg;
			drive_msg.direction = direction;
			drive_msg.speed = speed;
			drive_pub.publish(drive_msg);
		}

		//checking to see if the q button has been pressed to quit
		if(in == 'q'){
				printw("Exiting\n");
				refresh();
				endwin();
				return 0;
		}

		ros::spinOnce();
	}
}
