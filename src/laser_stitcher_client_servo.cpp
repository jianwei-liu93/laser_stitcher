
#include <ros/ros.h>
#include "laser_stitcher/stationary_scan.h"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "laser_stitcher_client");

	ros::NodeHandle nh;
	ros::ServiceClient scanning_client = nh.serviceClient<laser_stitcher::stationary_scan>("laser_stitcher/stationary_scan");

	bool should_loop;
	nh.param<bool>("laser_stitcher/should_loop", should_loop, false);
	int num_scans = 0;

	while(ros::ok() && (should_loop || num_scans == 0))
	{
		laser_stitcher::stationary_scan scan_srv;
		float temp_angle;
		if(!nh.param<float>("servo_manager_positional/min_angle", temp_angle, -1.57))
			if(!nh.param<float>("lidar_servo_manager/min_angle", temp_angle, -1.57))
				ROS_WARN_STREAM("[LaserStitcherClient] Unable to get min_angle variable from the parameter server - defaulting to " << temp_angle);
		scan_srv.request.min_angle = temp_angle;
		if(!nh.param<float>("servo_manager_positional/max_angle", temp_angle, -1.57))
			if(!nh.param<float>("lidar_servo_manager/max_angle", temp_angle, -1.57))
				ROS_WARN_STREAM("[LaserStitcherClient] Unable to get max_angle variable from the parameter server - defaulting to " << temp_angle);
		scan_srv.request.max_angle = temp_angle;
		scan_srv.request.external_angle_sensing = false;

		ros::Duration(2.0).sleep();

		ROS_INFO_STREAM("output message...");
		ros::Duration(2.0).sleep();
		if( ! scanning_client.call(scan_srv) )
			ROS_WARN_STREAM("[LaserStitcherClient] Scanning service call failed - prob not up yet");
		else
		{	
			ROS_INFO_STREAM("[LaserStitcherClient] Successfully called scanning service.");
			ROS_INFO_STREAM("\t Final cloud size: " << scan_srv.response.output_cloud.height*scan_srv.response.output_cloud.width << " in frame " << scan_srv.response.output_cloud.header.frame_id);
		}
		num_scans++;
	}
	
	ros::Duration(1.0).sleep();

}	