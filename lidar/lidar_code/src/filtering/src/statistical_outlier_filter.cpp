/*
* This code runs a StatisticalOutlierRemoval Filter which will remove noisy points from the 
* lidar scan 
*/

//ROS includes
#include <ros/ros.h>

//PCL includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/statistical_outlier_removal.h>

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

	//filtering out noisy points
	pcl::StatisticalOutlierRemoval<pcl::PCLPointCloud2> filter;
	filter.setInputCloud(cloud_ptr);
	filter.setMeanK(50);
	filter.setStddevMulThresh(1.0);
	filter.filter(filtered_cloud);

	//converting cloud data into pcl message
	sensor_msgs::PointCloud2 output;
	pcl_conversions::fromPCL(filtered_cloud, output);

	//publishing the filtered data
	cloud_output.publish(output);
}

int main(int argc, char** argv){

	//initializing ROS
	ros::init(argc, argv, "statistical_outlier_filter_node");
	ros::NodeHandle nh;

	//ROS subscriber
	cloud_input = nh.subscribe("passthrough_pcl", 1, pcl_cb);

	//ROS publisher
	cloud_output = nh.advertise<sensor_msgs::PointCloud2>("statistical_outlier_pcl", 1);

	//Main Loop
	while(ros::ok()){
		ros::spinOnce();
	}
}
