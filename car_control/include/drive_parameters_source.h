#pragma once

#include <ros/ros.h>

#include <drive_msgs/drive_param.h>
#include <std_msgs/Float64.h>
#include <functional>

/*
*  This node subscribes to all publishers drive_param messages and selects one to forward to the car controller
*/
class DriveParametersSource
{
    public:
    DriveParametersSource(ros::NodeHandle* node_handle, const char* topic, std::function<void(DriveParametersSource*, const drive_msgs::drive_param::ConstPtr&)> update_callback, int priority, double timeout);
    
    bool isOutdated();
    bool isIdle();
    int getPriority();

    private:
    ros::Subscriber m_drive_parameters_subscriber;

    int m_priority;
    long int m_timeout;
    bool m_idle;
    long int m_last_update;

    std::function<void(DriveParametersSource*, const drive_msgs::drive_param::ConstPtr&)> m_updateCallback;

    void driveParametersCallback(const drive_msgs::drive_param::ConstPtr& parameters);
};