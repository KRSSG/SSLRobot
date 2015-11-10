#include <iostream>
#include <cstring>
#include <ctime>
#include "krssg_ssl_msgs/BeliefState.h"
#include "tactics/tactic_factory.h"
#include <stdio.h>

#include "ros/ros.h"
#include "rj_robot.h"
#include <ssl_common/grSimComm.h>
using namespace std;


namespace Strategy {

  RJRobot::RJRobot(int botID, ros::NodeHandle &n): botID(botID), 
                                              gotTacticPacket(false), 
                                              n(n),
                                              commandPub(n.advertise<krssg_ssl_msgs::gr_Commands>("/grsim_data", 1000)),
                                              planner(Planning::PlannerForCommandType(Planning::MotionCommand::PathTarget)),
                                              controller(new MotionControl()),
                                              path(nullptr)
  {
    // lets make the default tactic = TPosition, pos = (0,0)
    curTactic = TacticFactory::instance()->Create("TPosition", botID);
    // tParam should already be 0,0,0 no need to set again.
    using namespace Planning;
    std::shared_ptr<Configuration> config =
          Configuration::FromRegisteredConfigurables();
  }

  RJRobot::~RJRobot() {}

  void RJRobot::beliefStateCallback(const krssg_ssl_msgs::BeliefState::ConstPtr &bs) {
    using namespace krssg_ssl_msgs;
    // printf("got beliefState\n");
    using namespace Planning;
    using Geometry2d::Point;

    // printf("bot %d: (%f, %f)\n", botID, bs->homePos[botID].x, bs->homePos[botID].y);
    MotionInstant mi({1,1},{0,0});
    std::unique_ptr<MotionCommand> mc(new PathTargetCommand(mi));
    Geometry2d::ShapeSet obstacles;
    path = planner->run(MotionInstant(), mc.get(), MotionConstraints(), &obstacles, std::move(path));
    std::unique_ptr<RotationCommand> rc = std::make_unique<RotationCommand>(FacePointCommand({1,1}));
    Point robot_pos(bs->homePos[botID].x/1000., bs->homePos[botID].y/1000.);
    float robot_angle = bs->homePos[botID].theta;
    MotionConstraints motionConstraints;
    RotationConstraints rotationConstraints;
    MotionWrapper w = controller->run(path.get(), rc.get(), mc.get(), robot_pos, robot_angle, motionConstraints, rotationConstraints);

    // gr_Robot_Command robot_command = curTactic->execute(*bs, curParam);
    gr_Robot_Command robot_command = Strategy::getRobotCommandMessage(botID, -w.vel.y*1000., w.vel.x*1000., w.w, 0, 0);
    gr_Commands command;
    command.robot_commands = robot_command;
    command.timestamp = ros::Time::now().toSec();
    command.isteamyellow = bs->isteamyellow;
    commandPub.publish(command);
  }
  void RJRobot::tacticPacketCallback(const krssg_ssl_msgs::TacticPacket::ConstPtr& tp) {
  //   printf("got tactic packet for bot (%d), tactic = (%s)\n", botID, tp->tID.c_str());
  //   tParamJSON = tp->tParamJSON;
  //   tID = tp->tID;
  //   gotTacticPacket =  true;
  }

}

