#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include "my_pkg/numbers.h"

using namespace nav_msgs;
using namespace geometry_msgs;
  ros::Publisher chatter_pub;
  ros::ServiceClient client;
  Pose target;
  geometry_msgs::Twist msg;
  float distance_x=0;
  float distance_y=0;
  int k=2;


  void chatterCallback(const Odometry:: Ptr& x){
    distance_x=target.position.x-x->pose.pose.position.x;
    distance_y=target.position.y-x->pose.pose.position.y;
    if((distance_x>=-0.1 && distance_x<=0.1) && (distance_y>=-0.1 && distance_y<=0.1))
      {
        my_pkg::numbers srv;
        srv.request.min= -6;
        srv.request.max= 6;
        client.call(srv);
        target.position.x=srv.response.a;
        target.position.y=srv.response.b;
      }

    else
      {
        msg.linear.x=k*distance_x;
        msg.linear.y=k*distance_y;
        chatter_pub.publish(msg);
      }
  }

int main(int argc, char **argv)
{

  target.position.x=0;
  target.position.y=0;
  ros::init(argc, argv, "first_process");
  ros:: NodeHandle n2;
  ros:: NodeHandle n3;
  ros:: NodeHandle n4;
  client= n2.serviceClient<my_pkg::numbers>("random");
  chatter_pub= n3.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros:: Subscriber robot_position= n4.subscribe("odom", 1000, chatterCallback);
  ros:: spin();
  return 0;
}


