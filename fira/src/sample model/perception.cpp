#include "ros/ros.h"
#include "std_msgs/String.h"
 
void Callback1(const std_msgs::String::ConstPtr& cammsg)
{
  
  ROS_INFO("[Perciever] I am getting: [%s]\n", cammsg->data.c_str());
  
}
void Callback2(const std_msgs::String::ConstPtr& enmsg)
{
  
  ROS_INFO("[Perciever] I am getting: [%s]\n", enmsg->data.c_str());
  
}
void Callback3(const std_msgs::String::ConstPtr& imumsg)
{
  
  ROS_INFO("[Perciever] I am getting: [%s]\n", imumsg->data.c_str());
  
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "perception");

  
  ros::NodeHandle n,m,p;

  
  ros::Subscriber sub1 = n.subscribe("camraw", 1000,Callback1);
ros::Subscriber sub2 = m.subscribe("enraw", 1000,Callback2);
ros::Subscriber sub3= p.subscribe("imuraw", 1000,Callback3);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}
