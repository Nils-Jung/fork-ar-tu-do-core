#include "drive_parameters_source.h"
#include <math.h>

constexpr auto DEFAULT_TIME = std::chrono::steady_clock::time_point::min();

DriveParametersSource::DriveParametersSource(ros::NodeHandle* node_handle, const char* topic,
                                             DriveParameterCallbackFunction update_callback, DriveMode drive_mode,
                                             double timeout)
{
    ROS_ASSERT_MSG(drive_mode != DriveMode::LOCKED, "Don't define a drive parameter source for the LOCKED mode.");
    
    this->m_drive_parameters_subscriber =
        node_handle->subscribe<drive_msgs::drive_param>(topic, 1, &DriveParametersSource::driveParametersCallback,
                                                        this);
    this->m_drive_mode = drive_mode;
    this->m_idle = true;
    this->m_updateCallback = update_callback;
    this->m_timeout = std::chrono::duration<double>(timeout);
    this->m_last_update = DEFAULT_TIME;
}

void DriveParametersSource::driveParametersCallback(const drive_msgs::drive_param::ConstPtr& message)
{
    this->m_last_update = std::chrono::steady_clock::now();
    this->m_idle = fabs(message->velocity) < IDLE_RANGE && fabs(message->angle) < IDLE_RANGE;
    this->m_updateCallback(this, message);
}

bool DriveParametersSource::isOutdated()
{
    if (this->m_last_update == DEFAULT_TIME)
    {
        return true;
    }
    return this->m_last_update + this->m_timeout < std::chrono::steady_clock::now();
}

bool DriveParametersSource::isIdle()
{
    return this->m_idle;
}

DriveMode DriveParametersSource::getDriveMode()
{
    return this->m_drive_mode;
}