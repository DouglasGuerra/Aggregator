/*
* This code filters out values in the x direction, that are farther than the starting area where 
* the robot could be placed. This is done through a PassThrough filter. The right side of the lidar
* is where the mini-usb port is connected. The notch, indicates the back of the lidar where no 
* data points are acquired
*
*/

//For ROS
#include <ros/ros.h>

//For PCL
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/passthrough.h>

//Subscriber and publisher for the pointcloud data
ros::Subscriber cloud_input;
ros::Publisher cloud_output;

void pcl_cb(const sensor_msgs::PointCloud2ConstPtr& input_cloud){

	//converting ros msg to pcl cloud
	pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
	pcl::PCLPointCloud2Ptr cloud_ptr(cloud);

	//converting the msg to PCL data
	pcl_conversions::toPCL(*input_cloud, *cloud);

	//creating an output cloud to hold the filtered data
	pcl::PCLPointCloud2 filtered_cloud;

	//filtering out in the x direction
	pcl::PassThrough<pcl::PCLPointCloud2> filter;
	filter.setInputCloud(cloud_ptr);
	filter.setFilterFieldName("y");
	filter.setFilterLimits(-1.1025, 2.6775);
	filter.filter(filtered_cloud);

	//converting cloud data into pcl message
	sensor_msgs::PointCloud2 output;
	pcl_conversions::fromPCL(filtered_cloud, output);

	//publishing the filtered data
	cloud_output.publish(output);
}

int main(int argc, char** argv){

	//initializing ROS
	ros::init(argc, argv, "passthrough_filter_node");
	ros::NodeHandle nh;

	//ROS subscriber
	cloud_input = nh.subscribe("lidar_pcl", 1, pcl_cb);

	//ROS publisher
	cloud_output = nh.advertise<sensor_msgs::PointCloud2>("passthrough_pcl", 1);


	//Main Loop
	while(ros::ok()){
		ros::spinOnce();
	}
}

