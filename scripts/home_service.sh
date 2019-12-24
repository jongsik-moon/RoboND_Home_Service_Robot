#!/bin/sh
cd $(pwd)/../..

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/src/map/world.world" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/src/map/world.yaml" &
sleep 5
xterm -e "rosrun rviz rviz -d $(pwd)/src/rvizConfig/default.rviz" &
sleep 5
xterm -e "source devel/setup.bash; rosrun add_markers add_markers"&
sleep 5
xterm -e "source devel/setup.bash; rosrun pick_objects pick_objects"

