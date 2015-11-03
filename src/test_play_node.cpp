#include <iostream>
#include <cstring>
#include <ctime>
#include "krssg_ssl_msgs/BeliefState.h"
#include <stdio.h>

#include "ros/ros.h"
#include <krssg_ssl_msgs/TacticPacket.h>
#include <tactics/tactic_factory.h>
#include <string>
int main(int argc, char  *argv[])
{
  // send a dummy TacticPacket
  using namespace Strategy;
  ros::init(argc, argv, "test_play_node");
  ros::NodeHandle n;
  ros::Publisher tp_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_0", 1000);
  while (ros::ok()) {
    krssg_ssl_msgs::TacticPacket tp;
    tp.tID = std::string("TPosition");
    double x, y;
    printf("enter gotopoint coordinates:\n");
    Tactic::Param tParam;
    scanf("%f %f", &tParam.PositionP.x, &tParam.PositionP.y);
    tp.tParamJSON = TacticFactory::instance()->Create("TPosition", 0)->paramToJSON(tParam); // bot id really doesnt matter here
    tp_pub.publish(tp);
    ros::spinOnce();
  }
  return 0;
}