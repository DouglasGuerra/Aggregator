/*
* This code  extracts the best fit line from the point cloud data set. Then it analyzes the line to
* ensure it is our desired object. Then we pass this object as a ROS msg. 
*/

#include <math.h>

//ROS includes
#include <ros/ros.h>
#include "ros/time.h"
#include "shared_files/position.h"
#include "shared_files/angle_rotation.h"

//PCL includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/sample_consensus/sac_model_line.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/common/centroid.h>
#include <pcl/filters/extract_indices.h>

//Subscriber and publisher for the pointcloud data
ros::Subscriber sub_input;
ros::Publisher pub_output;
ros::Publisher pos_pub;

//defining the length of our object in meters
const float object_length = 0.5969;
const float length_min = object_length - 0.15;	//setting a range of +/- 0.05 meters
const float length_max = object_length + 0.15;

//global variables
const int max_angle_deviation = 10;		//the biggest angle deviation from being parallel to the dumping site
const float max_center_deviation = 0.25;	//this is the range we give from the object being centered. Meaning our objects center can be +/- 0.15 from the position of lidar
const int max_proximity = 0.25;			//the closest we can get to the dumping site during orientation

//defining a constant for pi, which is going to be used to calculate the angle of 
//orientation for object
const double pi = 3.1415926;
float angle = 0;

//Variables that are used to write to msg files
shared_files::angle_rotation rotation_msg;
shared_files::position pos_msg;

/*
* Function Name: pcl_cb
* Description: This is a callback function that is called when there is statistical_outlier_node 
*	       publishes data, which is a point cloud. We then segment the point cloud until we find
*	       our object in this cluster. Then we publish this object, which will be processed by
*	       compute_centroid_node.
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

	//Creating an empty PointCloud to contain all of the inliers, points that are form the segmentation
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inliers(new pcl::PointCloud <pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud <pcl::PointXYZ>);

	//Creating the extraction object to remove inliers from the cloud, if it doesn't represent 
	//our object
	pcl::ExtractIndices<pcl::PointXYZ> extract;

	//Function to calculate the centroid of the object
	Eigen::Vector4f centroid;

	//PointCloud variable that is needed to output as ROS Msg
	sensor_msgs::PointCloud2 output;

	//variables to calculate the length of the detected object
	float dist_x = 0;
	float dist_y = 0;
	float dist_object = 0;

	/*
	A loop that continues until we find our desired object or there are no segments that
	we can process
	*/
	bool found_object = false;
	bool gotInliers = true;
	while(!found_object && gotInliers){
		//setting the parameters of the segmentation object
		seg.setModelType(pcl::SACMODEL_LINE);
		seg.setMethodType(pcl::SAC_RANSAC);
		seg.setDistanceThreshold(0.01);

		//performing the segmentation
		seg.setInputCloud(cloud);
		seg.segment(*inliers, coefficients);

		//No objects were find that fulfill our parameters so we break out of the loop
		if(inliers->indices.size() <= 20){
			gotInliers = false;
			break;
		}
		else{ //We have inliers so we can continue

			//extracting the inliers from the original cloud
			extract.setInputCloud(cloud);
			extract.setNegative(false);
			extract.setIndices(inliers);
			extract.filter(*cloud_inliers);

			//Determining the minimum and maximum points of the cluster
			pcl::PointXYZ minPoint, maxPoint;
			pcl::getMinMax3D(*cloud_inliers, minPoint, maxPoint);

			//Determining the distance between minimum and maximum of x and y coordinates
			dist_x = maxPoint.x - minPoint.x;
			dist_y = maxPoint.y - minPoint.y;

			//Calculating the object length of extracted image, using euclidean distance
			dist_object = pow(dist_x, 2) + pow(dist_y, 2);
			dist_object = pow(dist_object, 0.5);

			//publishing the object that has been extracted
			pcl::toROSMsg(*cloud_inliers, output);
			pub_output.publish(output);

			//we have found our object
			if(dist_object >= length_min && dist_object <= length_max){
				//The distance of the object we found is within the desired range
				found_object = true;
				break;
			}
			else{
				//Removing the extracted indices from the original cloud so we are left with a reduced cloud
				extract.setInputCloud(cloud);
				extract.setNegative(true);
				extract.setIndices(inliers);
				extract.filter(*cloud);
			}
		}
	}

	//We determine which message to send, we only want to send a message every 0.1 of a second
	if(found_object){

		pos_msg.found = 1; 	//writing msg that we have found our object

		/*
		* computing the centroid of the object
		* Centroid contains the distance of the centroid of the object to the lidar
		* Centroid[1] refers to the distance to the left or right (y-axis)
		* Centroid[0] refers to the distance from the front (x-axis)
		*/
		pcl::compute3DCentroid(*cloud_inliers, centroid);

		//Inversing the y-axis, since the left is givn as positive and right as negative
		centroid[1] = -1*centroid[1];

		//ROS_INFO("X: %f, Y: %f, Z: %f", centroid[0], centroid[1], centroid[2]);
		if(centroid[0] < max_proximity){
			pos_msg.direction = 0;		//we want to stop moving
			pos_msg.rotation_enable = 0;    //we are not centered so we don't want to enable rotation
		}
		else if(centroid[1] < -max_center_deviation){
			pos_msg.direction = 1;		//we want to move right
			pos_msg.position = -1; 		//we are on the left side of the arena
			pos_msg.rotation_enable = 0; 	//we are not centered so we don't want to enable rotation
		}
		else if(centroid[1] > max_center_deviation){
			pos_msg.direction = -1;		//we want to move left
			pos_msg.position = 1;		//we are on the right side of the arena
			pos_msg.rotation_enable = 0; 	//we are not centered so we don't want to enable rotation
		}
		else{

			pos_msg.position = 0;		//we are centered
			pos_msg.rotation_enable = 1;	//we are centered so we want to enable rotation

			/*
			* We are centered but we need to ensure that our robot is oriented to be parallel with the dumping area
			* To do this we use the x-value, since it represents the distance to the front of the lidar.
			* 	left_x represents the x-value of the leftmost point of the object, from perspective of the lidar
			*	right_x represents the x_value of the rightmost posint of the object, from perspective of the lidar
			*	angle represents our angle of deviation from the y-axis (axis representing the axis extending from the sides of the lidar)
			*/
			float right_x = cloud_inliers->points[0].x;
			float left_x = cloud_inliers->points[cloud_inliers->points.size()-1].x;
			angle = (180 / pi) * atan(dist_x / dist_y);

			//ROS_INFO("Angle: %f, Right_x: %f, Left_x: %f", angle, right_x, left_x);
			if (left_x < right_x && angle > max_angle_deviation){
				pos_msg.rotation_direction = 1;		//rotate clockwise
				pos_msg.angle = angle; 			//specifying the angle of rotation
			}
			else if(left_x > right_x && angle > max_angle_deviation){
				pos_msg.rotation_direction = -1;	//rotate counter-clockwise
				pos_msg.angle = angle;			//specifying the angle of rotation
			}
			else{
				pos_msg.rotation_direction = 0;		//we are oriented
				pos_msg.angle = 0;
			}
		}
	}
	else{
		pos_msg.found = 0;		//object not found
		pos_msg.rotation_enable = 0;
	}

	pos_pub.publish(pos_msg);
	ROS_INFO("Sent information\n");
}

int main(int argc, char** argv){

	//initialize a node
	ros::init(argc, argv, "calc_position_node");
	ros::NodeHandle nh;

	//Create a ROS subscriber for the input data from the lidar
	//Calls callback function pcl_cb
	sub_input = nh.subscribe("/filter_output_pcl", 1000, pcl_cb);

	//to publish object line, for debugging
	pub_output = nh.advertise<sensor_msgs::PointCloud2>("output_line", 1);

	//publishing to msgs
	pos_pub = nh.advertise<shared_files::position>("position_val", 10);

	//Main Loop
	while(ros::ok()){
		ros::spinOnce();
	}
}
