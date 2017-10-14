/*
* This code  extracts the best fit line from the point cloud data set. Then it analyzes the line to
* ensure it is our desired object. Then we pass this object as a ROS msg. 
*/

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
float object_length = 0.4064;
float length_min = object_length - 0.05;	//setting a range of +/- 0.05 meters
float length_max = object_length + 0.05;

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

	//variables to calculate the length of the detected object
	float dist_x = 0;
	float dist_y = 0;
	float dist_object = 0;
	/*
	A loop that continues until we find our desired object or there are no segments that
	we can process
	*/
	bool found_object = false;
	bool gotInliers = false;
	while(!found_object || gotInliers){
		//setting the parameters of the segmentation object
		seg.setModelType(pcl::SACMODEL_LINE);
		seg.setMethodType(pcl::SAC_RANSAC);
		seg.setDistanceThreshold(0.001);

		//performing the segmentation
		seg.setInputCloud(cloud);
		seg.segment(*inliers, coefficients);

		//No objects were find that fulfill our parameters so we break out of the loop
		if(inliers->indices.size() == 0){
			std::cout << "No inliers" << std::endl;
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

			if(dist_object >= length_min && dist_object <= length_max){
				//The distance of the object we found is within the desired range
				found_object = true;
				output_cloud = cloud_inliers;
				ROS_INFO("FOUND IT!!!!!!!!!!!!!!!!!!!!!\n");
			}

			if(!found_object) {
				//Removing the extracted indices from the original cloud so we are left with a reduced cloud
				extract.setInputCloud(cloud);
				extract.setNegative(true);
				extract.setIndices(inliers);
				extract.filter(*cloud);
			}
		}
	}

	ROS_INFO("We are out of the while loop");
	//Creating a ROS msg
	sensor_msgs::PointCloud2 output;
	pcl::toROSMsg(*output_cloud, output);

	//Publishing a ROS msg
	pub_output.publish(output);
}

int main(int argc, char** argv){

	//initialize a node
	ros::init(argc, argv, "ransac_node");
	ros::NodeHandle nh;

	//Create a ROS subscriber for the input data from the lidar
	//Calls callback function pcl_cb
	sub_input = nh.subscribe("/statistical_outlier_pcl", 1000, pcl_cb);

	//ROS publisher
	// This is done for debugging to see it in rviz
	pub_output = nh.advertise<sensor_msgs::PointCloud2>("pcl_line", 1);

	//Main Loop
	while(ros::ok()){
		ros::spinOnce();
	}
}
