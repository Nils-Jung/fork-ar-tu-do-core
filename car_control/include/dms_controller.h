#pragma once

#include <ros/ros.h>

#include <chrono>
#include <std_msgs/Int64.h>
#include <std_msgs/Int32.h>

constexpr const char* PARAMETER_DMS_CHECK_RATE = "dms_check_rate";
constexpr const char* PARAMETER_DMS_EXPIRATION = "dms_expiration";

constexpr const char* TOPIC_HEARTBEAT_MANUAL = "/input/heartbeat_manual";
constexpr const char* TOPIC_HEARTBEAT_AUTONOMOUS = "/input/heartbeat_autonomous";
constexpr const char* TOPIC_DRIVE_MODE = "/commands/drive_mode";

enum class DriveMode : int
{
    LOCKED = 0,
    MANUAL = 1,
    AUTONOMOUS = 2
};

class DMSController
{
    public:
    DMSController();

    void spin();

    private:
    /**
     * @brief How often the unlock motor message is published, in Hz
     */
    int m_update_frequency;

    /**
     * @brief How old the last dead man's switch heartbeat can be, in ms
     */
    std::chrono::duration<double> m_expiration_time;

    std::chrono::steady_clock::time_point m_last_heartbeat_manual;
    std::chrono::steady_clock::time_point m_last_heartbeat_autonomous;

    ros::NodeHandle m_node_handle;
    ros::Subscriber m_heartbeat_manual_subscriber;
    ros::Subscriber m_heartbeat_autonomous_subscriber;
    ros::Publisher m_drive_mode_publisher;

    void configureParameters();
    void publishDriveMode();

    void heartbeatManualCallback(const std_msgs::Int64::ConstPtr& dms_message);
    void heartbeatAutonomousCallback(const std_msgs::Int64::ConstPtr& dms_message);
    DriveMode getDriveMode();
};
