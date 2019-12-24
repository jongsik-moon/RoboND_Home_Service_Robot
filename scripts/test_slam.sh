#!/bin/sh
cd $(pwd)/../..

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/src/map/world.world" &
sleep 5
xterm -e "rosrun rviz rviz -d $(pwd)/src/rvizConfig/default.rviz" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch"
