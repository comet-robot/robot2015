		#include <ros/ros.h>
		#include <cmath>
		#include <std_msgs/Bool.h>
		//#include <geometry_msgs/Point.h>
		
		
		class BlockageDetector {
		    protected:
		        ros::Subscriber odometry_sub_;
		        ros::Subscriber motor_command_sub_;
		      
		        ros::Publisher blockage_pub_;

				//Mandatory
		        ros::NodeHandle nh_;
		        
		        // global variables
		        double tolerance;
		        geometry_msgs::Point motor_command_stored;
		        
		        

		
		    protected: // ROS Callbacks
		
				// This callback stores the motor command everytime one is recieved.
		        void motor_command_callback(const geometry_msgs::Point msg) {
					ROS_INFO("motor callback called");
					motor_command_stored = msg;
		            }
		        
		        // This one is triggered by the reception of an angle and coordinates and computes the floor plane.
		        void odometry_callback(const geometry_msgs::Point msg) {
					ROS_INFO("odometry callback called");
					//bool blockage_detected = true;
					std_msgs::Bool blockage_detected;
					blockage_detected.data = sqrt((msg.x - motor_command_stored.x)*(msg.x - motor_command_stored.x) + (msg.y - motor_command_stored.y)*(msg.y - motor_command_stored.y)) < tolerance ;     
		            
		            blockage_pub_.publish(blockage_detected);
		            }
		
		    public:
		        BlockageDetector() : nh_("~") {
		            nh_.param("tolerance",tolerance,10.0);
		            
		            //test debug
		            assert(tolerance > 0);
		           
		            //ROS_INFO("c: %d value in [%f, %f]",n_c,c_min,c_max);
		
					//just in case
		            ros::Duration(0.5).sleep();
		
		            odometry_sub_ = nh_.subscribe("odometry",1,&BlockageDetector::odometry_callback,this);
		            motor_command_sub_ = nh_.subscribe("motor_command",1,&BlockageDetector::motor_command_callback,this);
		            //blockage_pub_ = nh_.advertise<std_msgs::Bool>("blockage",1);
		
		        }
		
		};
		
		int main(int argc, char * argv[]) 
		{
		    ros::init(argc,argv,"blockage_detection");
		    BlockageDetector bd;
		
		    ros::spin();
		    return 0;
		}
