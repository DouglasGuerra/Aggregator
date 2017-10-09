#include <iostream>
#include <math.h>

//ROS includes
#include <ros/ros.h>

//PCL includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/sample_consensus/sac_model_line.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/filters/extract_indices.h>

//Subscriber and publisher for the pointcloud data
ros::Subscriber sub_input;
ros::Publisher pub_output;

//defining the length of our object in meters
float object_length = 1;

/*
* Function Name: pcl_cb
* Description: This is a callback function that is called when there is statistical_outlier_node 
*              publishes data, which is a point cloud. We then segment the point cloud until we find
*              our object in this cluster. Then we publish this object, which will be processed by
*              compute_centroid_node.
*/
void pcl_cb(const sensor_msgs::PointCloud2ConstPtr& input){

        //Converting the input data from a ROS msg to a pcl cloud
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromROSMsg(*input, *cloud);

        //Creating variables to hold the coefficients and inliers of the cloud
        //inliers are the points that are part of the extraction
        pcl::ModelCoefficients coefficients;
        pcl::PointIndices::Ptr inliers (new pcl::PointIndices());

        //Creating the segmentaion object
        pcl::SACSegmentation<pcl::PointXYZ> seg;

	//setting the parameters of the segmentation object
        seg.setModelType(pcl::SACMODEL_LINE);
        seg.setMethodType(pcl::SAC_RANSAC);
        seg.setDistanceThreshold(0.001);

        //performing the segmentation
        seg.setInputCloud(cloud);
        seg.segment(*inliers, coefficients);
 
	//Removing the extracted indices from the original cloud, and remaining with the original data set
	pcl::ExtractIndices<pcl::PointXYZ> extract;
	extract.setInputCloud(cloud);
	extract.setNegative(false);
	extract.setIndices(inliers);
	extract.filter(*cloud);

	pcl::PointXYZ minPoint, maxPoint;
	pcl::getMinMax3D(*cloud, minPoint, maxPoint);

	float dist_x = maxPoint.x - minPoint.x;
	float dist_y = maxPoint.y - minPoint.y;

	//calculating euclidean distance
	float dist = (pow(dist_x, 2) + pow(dist_y, 2));
	dist  = pow(dist, 0.5);
	std::cout << "X: " << dist_x << " Y: " << dist_y << std::endl;
	std::cout << "dist: " << dist << std::endl;

	//Creating a ROS msg
        sensor_msgs::PointCloud2 output;
        pcl::toROSMsg(*cloud, output);

        //Publishing a ROS msg
        pub_output.publish(output);
}

int main(int argc, char** argv){

        //initialize a node
        ros::init(argc, argv, "extract_indices_node");
        ros::NodeHandle nh;

        //Create a ROS subscriber for the input data from the lidar
        //Calls callback function pcl_cb
        sub_input = nh.subscribe("/statistical_outlier_pcl", 1000, pcl_cb);

        //ROS publisher
        // This is done for debugging to see it in rviz
        pub_output = nh.advertise<sensor_msgs::PointCloud2>("pcl_extract", 1);

        //Main Loop
        while(ros::ok()){
                ros::spinOnce();
        }
}
