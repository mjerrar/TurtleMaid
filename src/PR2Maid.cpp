/**
 * Copyright (C) 2018  Jerrar Bukhari
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
* @Author: Jerrar Bukhari
* @Date:   2018-12-16 16:15:14
* @Last Modified by:   Jerrar Bukhari
* @Last Modified time: 2018-12-16 05:42:34
*/

#include <ros/ros.h>
#include <iostream>
#include "PR2Maid/LegoBrick.h"
#include "PR2Maid/DropBin.h"
#include "PR2Maid/BrickList.h"
#include "PR2Maid/GlobalPlanner.h"
#include "PR2Maid/LocalPlanner.h"

/**
 * @brief      Callback funtion for previewing the plan
 *
 * @param[in]  msg   The message
 */
void cb(const nav_msgs::Path::ConstPtr& msg) {
  ROS_INFO_STREAM(msg->poses[0].pose.position.x);
}


/**
 * @brief      main function for planning
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 *
 * @return     true for succesful completion
 */
int main(int argc, char** argv) {
    ros::init(argc, argv, "pr2_main");
    ros::NodeHandle nh;
    ROS_INFO("doing");
    ros::Subscriber sub = nh.subscribe("move_base_node/NavfnROS/plan",
                                       1, cb);
    GlobalPlanner planner(nh);
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "base_footprint";
    goal.target_pose.pose.position.x = -2;
    goal.target_pose.pose.position.y = 0;
    goal.target_pose.pose.position.z = 0;
    goal.target_pose.pose.orientation.w = 1;
    planner.setGoal(goal);
    geometry_msgs::Pose zero_pose;
  LocalPlanner driver(nh);
  driver.Drive(zero_pose);

return 0;
}
