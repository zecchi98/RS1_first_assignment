# RS1_first_assignment
First assignment of research track 1
#RUN
How to run the package?
-roscore
-rosrun stage_ros stageros $(rospack find my_pkg)/world/exercise.world
-rosrun my_pkg second_process
-rosrun my_pkg first_process


#PACKAGE
How is the package composed?
The package is composed of 2 nodes and 1 server.
NODES:
- first_process
- second_process

SERVER:
- numbers

How the package works?
The "second_process" node will just be used to wait for a service request. The "first_process" will use it to generate a random target to reach.
The "first_process" node will check if the actual position of the "robot" corresponds to the target, if the target has been reached it will ask for another target. Otherwise it will compute and publish
the parameters to solve this problem.
#WHY THIS CHOICE
I choose to create this two kind of main nodes in order to sort of rapresents a keyboard/joystick/input node and an output node.
I choose to insert the "manual_goal" service inside the "commands.cpp" file just to limitate the number of nodes. But it would be obviously possible to insert it also inside another cpp file.
