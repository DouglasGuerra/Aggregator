/*
This code transforms the raw laser scan from the hokuyo lidar into PointCloud2 data which 
is then published as a ros message.
*/

#include <ros/ros.h>

//includes for PCL
#include <pcl_ros/point_cloud.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <laser_geometry/laser_geometry.h>

//defining a publisher
ros::Publisher pub_cloud;

//defining a subscriber
ros::Subscriber sub_input;

laser_geometry::LaserProjection projector; 	//converts from laser scan to pointcloud2

void scanCallBack(const sensor_msgs::LaserScan::ConstPtr& input){

	//Creates a pointCloud2 data type called output
	sensor_msgs::PointCloud2 output;

	//doing the conversion
	projector.projectLaser(*input, output);

	//Publish the data
	pub_cloud.publish(output);
}

int main(int argc, char **argv){

	//Initialize ROS
	ros::init(argc, argv, "convert_input_cloud_node");
	ros::NodeHandle nh;

	//Create a ROS subscriber for the input data from the lidar
	sub_input = nh.subscribe("/scan", 1, scanCallBack);

	//Create a ROS publisher for the output point cloud
	pub_cloud = nh.advertise<sensor_msgs::PointCloud2>("lidar_pcl", 1);

	//Main Loop
	while(ros::ok()){
		ros::spinOnce();
	}
}
