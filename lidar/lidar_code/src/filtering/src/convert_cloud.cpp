/***************************************************************************************************
* This code transforms the raw laser scan from the hokuyo lidar into PointCloud2 data. This data 
* is then filtered using both the PassThrough and StatisticalOutlierRemoval filter. The output data
* is then put onto a ros message.
**************************************************************************************************/

//ROS includes
#include <ros/ros.h>
#include "ros/time.h"

//PCL includes
#include <pcl_ros/point_cloud.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <laser_geometry/laser_geometry.h>


//defining a subscriber (read input cloud from lidar) and publisher (to publish filtered data)
ros::Publisher pub_cloud;
ros::Subscriber sub_input;

//Timing variables
ros::Time last_time, current_time;
ros::Duration publish_time(0.05);	//we want to send a message every 0.05 milliseconds
					//do not want to overload with messages

//defining object that converts laser scan to pointcloud2 type 
laser_geometry::LaserProjection projector;

/***************************************************************
* Function Name: scanCallBack
* Description: This function is called when a new lidar scan is read
*		and it then filters the raw data and then outputs the filtered
*		cloud as a ros message.
***************************************************************/
void scanCallBack(const sensor_msgs::LaserScan::ConstPtr& cloud_scan){

  current_time = ros::Time::now();
  if(current_time - last_time > publish_time){
	//converting our raw scan into a pointcloud2 type so we can filter
	sensor_msgs::PointCloud2 temp_cloud;
	projector.projectLaser(*cloud_scan, temp_cloud);
	pcl::PCLPointCloud2* input_cloud = new pcl::PCLPointCloud2;
	pcl_conversions::toPCL(temp_cloud, *input_cloud);

	/*
	* PassThrough Filter implementation:
	*	Filtering out data in the y-direction (right and left of the lidar).
	*	Points that lie outside of the starting area of the robot are eliminated.
	*	Assumption, is that the back of the lidar is where the notch is and the right
	*	side of the lidar is where the mini-usb connector is.
	*/
	pcl::PCLPointCloud2Ptr cloud_ptr_1(input_cloud);	//pointer to our input cloud
	pcl::PCLPointCloud2* passthrough_out_cloud = new pcl::PCLPointCloud2;	//cloud to hold output of filter

	pcl::PassThrough<pcl::PCLPointCloud2> passthrough;
	passthrough.setInputCloud(cloud_ptr_1);
	passthrough.setFilterFieldName("y");
	passthrough.setFilterLimits(-1.1025, 2.6775);
	passthrough.filter(*passthrough_out_cloud);

	/*
	* Statistical Outlier Filter implementation
	*	Filtering out noisy data from our point cloud. We pass the output of the
	*	passthrough filter through this filter.
	*/
	pcl::PCLPointCloud2Ptr cloud_ptr_2(passthrough_out_cloud);
	pcl::PCLPointCloud2 output_cloud;

	pcl::StatisticalOutlierRemoval<pcl::PCLPointCloud2> stat_outlier;
	stat_outlier.setInputCloud(cloud_ptr_2);
	stat_outlier.setMeanK(10);
	stat_outlier.setStddevMulThresh(0.01);
	stat_outlier.filter(output_cloud);


	/*
	* Outputting our cloud through a ros message
	*/
	sensor_msgs::PointCloud2 output;
	pcl_conversions::fromPCL(output_cloud, output);
	pub_cloud.publish(output);

	last_time = ros::Time::now(); //marking the time we last sent a message
  }
}

/*
* Main Function
*/
int main(int argc, char **argv){

	//initializing ROS
	ros::init(argc, argv, "convert_cloud_node");
	ros::NodeHandle nh;

	//ROS subscriber
	sub_input = nh.subscribe("/scan", 1, scanCallBack);

	//ROS publisher
	pub_cloud = nh.advertise<sensor_msgs::PointCloud2>("filter_output_pcl", 1);

	//initiating time variables
	current_time = ros::Time::now();
	last_time = current_time;

	//Main Loop
	while(ros::ok())
		ros::spinOnce();
}
