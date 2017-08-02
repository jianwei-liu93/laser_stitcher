
#ifndef LASER_STITCHER_H
#define LASER_STITCHER_H

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <sensor_msgs/LaserScan.h>
#include <laser_geometry/laser_geometry.h>
#include <tf/transform_listener.h>
#include <pcl_conversions/pcl_conversions.h>

class LaserStitcher
{
public: 
	LaserStitcher();
private:
	ros::NodeHandle nh_;
	ros::Subscriber scan_sub_;
	ros::Subscriber finish_sub_;
	ros::Publisher cloud_pub_;

	bool is_running_;
	std::string target_frame_;
	sensor_msgs::PointCloud2 summed_pointcloud_;

	laser_geometry::LaserProjection scan_converter_;
	tf::TransformListener listener_;

	void laserCallback(const sensor_msgs::LaserScan::ConstPtr& scan_in);
	void setScanningState(const std_msgs::Bool::ConstPtr& shut_down);
};

#endif //LASER_STITCHER_H