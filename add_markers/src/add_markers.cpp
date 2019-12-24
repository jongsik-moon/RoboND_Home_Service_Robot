
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <math.h>

float odom_x = 0.0, odom_y = 0.0;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  odom_x = msg->pose.pose.position.x;
  odom_y = msg->pose.pose.position.y;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Subscriber obom_sub = n.subscribe("/odom", 10, odomCallback);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  float pickup[3] = {4.0, 0.0};
  float dropoff[3] = {2.0, -0.5};

  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "basic_shapes";
  marker.id = 0;
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = pickup[0];
  marker.pose.position.y = pickup[1];
  marker.pose.position.z = 0.5;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.scale.z = 0.5;
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();


  float reachTolerance = 0.2;

  bool deleted = false;
  bool reachedPickup = false;

  while (ros::ok())
  {

    float xdiffPickup = fabs(pickup[0] - odom_x);
    float ydiffPickup = fabs(pickup[1] - odom_y);

    float xdiffDropoff = fabs(dropoff[0] - odom_x);
    float ydiffDropoff = fabs(dropoff[1] - odom_y);

    if ((xdiffPickup < reachTolerance) && (ydiffPickup < reachTolerance) && !deleted && !reachedPickup){
      marker.action = visualization_msgs::Marker::DELETE;
      deleted = true;
      reachedPickup = true;
    }
    if ((xdiffDropoff < reachTolerance) && (ydiffDropoff < reachTolerance)  && reachedPickup){
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = dropoff[0];
      marker.pose.position.y = dropoff[1];
      marker.pose.position.z = 0.5;

      marker.scale.x = 0.5;
      marker.scale.y = 0.5;
      marker.scale.z = 0.5;

    }
    marker_pub.publish(marker);

    ros::spinOnce();
  }
  return 0;
}
