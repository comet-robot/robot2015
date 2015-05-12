/*
 * Subscriber for the motors (wheels)
 * Receives messages from RasPi,
 * computes what to tell to each motor
 * and orders them to run accordingly
 */
 
 #include <ros.h>
 #include <std_msgs/String.h>
 #include <std_msgs/Empty.h>
 #include <geometry_msgs/Point.h>
 #include <cmath>
 #include <std_msgs/Bool.h>
 
 ros::NodeHandle nh_;
 //final position
 //must add something to Point to indicate final angle
 geometry_msgs::Point stored_command;
 //current coordinates
 double position_x;
 double position_y;
 //current angle from horizontal
 double theta;
 
 //Treatment of the command (speed of each wheel if must move to whatever point)
 //might need to receive current point... Change message type accordingly
 
 
 
 //When a message is received, it gets stored
 void motor_callback(const geometry_msgs::Point msg){
  stored_command = msg;
 }

 //For message reception
 ros::Subscriber<geometry_msgs::Point> motor_sub_ = nh_.subscribe("motor",1,motor_callback,this);



void setup() {
  nh_.initNode();
  nh_.subscribe(motor_sub_);
  //add later the pins for each motor
  //pinMode(10, OUTPUT);
  //pinMode(11, OUTPUT);

}

void loop() {
  //first, check if straight trajectory
  //transform final coordinates in exp notation (angle only)
  //check "stored_command_x" notation...
  double rho = sqrt(stored_command_x*stored_command_x + stored_command_y*stored_command_y);
  double gamma = 
  
  
  

}
