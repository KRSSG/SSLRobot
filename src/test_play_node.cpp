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
  ros::Publisher tp0_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_0", 1000);
  ros::Publisher tp1_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_1", 1000);
  ros::Publisher tp2_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_2", 1000);
  ros::Publisher tp3_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_3", 1000);
  ros::Publisher tp4_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_4", 1000);

  krssg_ssl_msgs::TacticPacket tp0, tp1;
  ros::Rate loop_rate(1);
  tp0.tID = std::string("TPosition");
  Tactic::Param tParam;
  tp0.tParamJSON = TacticFactory::instance()->Create("TPosition", 0)->paramToJSON(tParam); // bot id really doesnt matter here

  tp1.tID = std::string("TKickToGoal");
  tp1.tParamJSON = TacticFactory::instance()->Create("TKickToGoal", 0)->paramToJSON(tParam); // bot id really doesnt matter here
  while (ros::ok()) {
   
    tp0_pub.publish(tp0);
    tp1_pub.publish(tp1);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}