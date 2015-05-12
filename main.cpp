#include "ros/ros.h"
#include "std_msgs/String.h"
#include <cmath>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Empty.h>

#include <sstream>

//Change name later, maybe reorganize in several classes...
class General {
	
	protected://Publishers and subscribers
	
		//Publishers for the motors (wheels); differentiation is made by the Arduino Due
		ros::Publisher motor_pub_ = nh_.advertise<geometry_msgs::Point>("motor",1);
  
		//Publishers for each servomotor (nature of the messages?)
		ros::Publisher servo_1_pub_ = nh_.advertise<geometry_msgs::Point>("servo 1",1);
		ros::Publisher servo_2_pub_ = nh_.advertise<geometry_msgs::Point>("servo 2",1);
  
		//Subscriber for the detection beacon
		ros::Subscriber beacon_sub_ = nh_.subscribe("beacon",1,&General::beacon_callback,this);
	
		//Subscriber for the odometers
		ros::Subscriber odometry_1_sub_ = nh_.subscribe("odometry 1",1,&General::odometry_1_callback,this);
		ros::Subscriber odometry_2_sub_ = nh_.subscribe("odometry 2",1,&General::odometry_2_callback,this);
		
		// global variables
		double tolerance;
		std_msgs::String beacon_message_stored;
		double odometry_1_message_stored;
		double odometry_2_message_stored;
	
	protected://ROS callbacks
		
		// This callback stores the beacon message everytime one is received.
		void beacon_callback(const std_msgs::String msg) {
			ROS_INFO("beacon callback called");
			beacon_message_stored = msg;
		}
		
		void odometry_1_callback(const double msg) {
			ROS_INFO("odometry callback 1 called");
			odometry_1_message_stored = msg;
		}
		
		void odometry_2_callback(const double msg) {
			ROS_INFO("odometry callback 2 called");
			odometry_2_message_stored = msg;
		}
	
}

//code a main_sth for each trajectory (main one, main one w/out servo, tests...)


int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle nh_;




  ros::Rate loop_rate(10);

 //switch on globalstate to decide which trajectory to follow
 
  
  while (ros::ok())
  {

    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();


    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
// %Tag(PUBLISH)%
    chatter_pub.publish(msg);
// %EndTag(PUBLISH)%

// %Tag(SPINONCE)%
    ros::spinOnce();
// %EndTag(SPINONCE)%

// %Tag(RATE_SLEEP)%
    loop_rate.sleep();
// %EndTag(RATE_SLEEP)%
    ++count;
  }


  return 0;
}
// %EndTag(FULLTEXT)%
