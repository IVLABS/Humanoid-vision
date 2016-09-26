#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "cam");

  
  ros::NodeHandle n;

  
  ros::Publisher cam_pub = n.advertise<std_msgs::String>("camraw", 1000);

  ros::Rate loop_rate(1);

  
  int count = 0;
  while (ros::ok())
  {
   
    std_msgs::String cammsg;

    std::stringstream ss;
    ss << "camera datastream " << count;
    cammsg.data = ss.str();

    ROS_INFO("I published %s\n", cammsg.data.c_str());

   
    cam_pub.publish(cammsg);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}