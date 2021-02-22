#include "ros/ros.h"
#include "std_msgs/String.h"
#include "my_pkg/numbers.h"

float randMToN(float M, float N);
bool myrandom(my_pkg::numbers::Request &req, my_pkg::numbers::Response &res);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "second_process");
  ros::NodeHandle n1;
  ros::ServiceServer service=n1.advertiseService("/random", myrandom);
  ros::spin();

  return 0;

}

/**
 *@brief this function given two inputs calculates one random number in the interval in between
 *@param M is the minimum number of the interval
 *@param N is the maximum number of the interval
 *@retval the random number
 */
float randMToN(float M, float N)
{
  return M+(rand() / (RAND_MAX / (N-M) ) ) ;
}

bool myrandom(my_pkg::numbers::Request &req, my_pkg::numbers::Response &res)
{
  res.a=randMToN(req.min, req.max);
  res.b=randMToN(req.min, req.max);
  ROS_INFO("New task: [%f, %f]", res.a, res.b);
  return true;
}

