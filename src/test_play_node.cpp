#include <iostream>
#include <cstring>
#include <ctime>
#include "krssg_ssl_msgs/BeliefState.h"
#include <stdio.h>
#include "ssl_common/config.h"
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
  ros::Publisher tp5_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_5", 1000);

  krssg_ssl_msgs::TacticPacket tp0, tp1,tp2,tp3,tp4,tp5;
  ros::Rate loop_rate(1);
  Tactic::Param tParam;
  //------------------------------------------
  tParam.PassToPointP.x=-HALF_FIELD_MAXX;
  tParam.PassToPointP.y=-HALF_FIELD_MAXY;
  tp0.tID = std::string("TPassToPoint");
  tp0.tParamJSON = TacticFactory::instance()->Create("TPassToPoint", 0)->paramToJSON(tParam); // bot id really doesnt matter here
  //------------------------------------------
  tParam.PassToPointP.x=-HALF_FIELD_MAXX;
  tParam.PassToPointP.y=-HALF_FIELD_MAXY;
  tp1.tID = std::string("TReceive");
  tp1.tParamJSON = TacticFactory::instance()->Create("TReceive", 0)->paramToJSON(tParam); // bot id really doesnt matter here
  //------------------------------------------
  tParam.PositionP.x=CENTER_X;
  tParam.PositionP.y=CENTER_Y;
  tParam.PositionP.finalSlope=0;
  tParam.PositionP.align=false;
  tp2.tID = std::string("TPosition");
  tp2.tParamJSON = TacticFactory::instance()->Create("TPosition", 0)->paramToJSON(tParam); // bot id really doesnt matter here
  //------------------------------------------
  tp3.tID = std::string("TPosition");
  tp3.tParamJSON = TacticFactory::instance()->Create("TPosition", 0)->paramToJSON(tParam); // bot id really doesnt matter here
  //------------------------------------------
  tp4.tID = std::string("TPosition");
  tp4.tParamJSON = TacticFactory::instance()->Create("TPosition", 0)->paramToJSON(tParam); // bot id really doesnt matter here
  //------------------------------------------
  tParam.PositionP.x=-HALF_FIELD_MAXX;
  tParam.PositionP.y=0;
  tParam.PositionP.finalSlope=0;
  tParam.PositionP.align=false;
  tp5.tID = std::string("TPosition");
  tp5.tParamJSON = TacticFactory::instance()->Create("TPosition", 0)->paramToJSON(tParam); // bot id really doesnt matter here
  
  while (ros::ok()) {
   
    tp0_pub.publish(tp0);
    tp1_pub.publish(tp1);
    tp2_pub.publish(tp2);
    tp3_pub.publish(tp3);
    tp4_pub.publish(tp4);
    tp5_pub.publish(tp5);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}