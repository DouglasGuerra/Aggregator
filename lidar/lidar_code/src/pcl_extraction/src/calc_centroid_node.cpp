/*
* This code takes in the extracted line from the point cloud data set. It calculates the centroid
* of the line, to tell us where the object is with respect to the lidar.
*
* X refers to the axis defined by the going straight out from the sides of the 
*  lidar.
*
* Y refers to the axis defined by going straight from the front of the lidar.  
*/

//ROS includes
#include <ros/ros.h>

//PCL includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/common.h>
#include <pcl/common/centroid.h>

//Subscriber to obtain the extracted line
ros::Subscriber extracted_line;

/*
* Function Name: pcl_cb
* Description: This is a callback function that is called when our ransac_node has found our
*	       desired object and is publishing it. We are now calculating the centroid of
*	       to determine its position from the lidar. 
*/
void pcl_cb(const sensor_msgs::PointCloud2ConstPtr& input){

	//Converting the input data from a ROS msg to a pcl cloud
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::fromROSMsg(*input, *cloud);

	//Calculating the centroid
	Eigen::Vector4f centroid;
	pcl::compute3DCentroid(*cloud, centroid);


	//Printing to console the calculated centroid
	//Centroid[1] refers to the distance of the centroid of the object to the left or right of lidar
	//Centroid[0] refers to the distance of the centroid of the object from the front of the lidar
	ROS_INFO("X: %f, Y: %f, Z: %f", centroid[1], centroid[0], centroid[2]);
}


int main(int argc, char **argv){

	//initializing a node for ros
	ros::init(argc, argv, "calc_centroid_node");
	ros::NodeHandle nh;

	//Create a ROS subscriber for the input data from ransac_node
	extracted_line = nh.subscribe("/pcl_line", 1000, pcl_cb);

	//Main Loop
	while(ros::ok()){
		ros::spinOnce();
	}
}
