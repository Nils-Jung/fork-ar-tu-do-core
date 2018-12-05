#pragma once

#include <ros/ros.h>

#include <drive_msgs/drive_param.h>
#include <sensor_msgs/Joy.h>

#define JOYSTICK_AXIS_STEERING 0
#define JOYSTICK_AXIS_THROTTLE 5
#define JOYSTICK_BUTTON_DEADMANSSWITCH 0

#define TOPIC_DRIVE_PARAMETERS "/set/drive_param"

class RemoteJoy
{
    public:
    RemoteJoy();

    private:
    ros::NodeHandle nodeHandle;
    ros::Publisher driveParametersPublisher;
    ros::Subscriber joystickSubscriber;

    void joystickCallback(const sensor_msgs::Joy::ConstPtr& joystick);
    void publishDriveParameters(double velocity, double steeringAngle);
};
