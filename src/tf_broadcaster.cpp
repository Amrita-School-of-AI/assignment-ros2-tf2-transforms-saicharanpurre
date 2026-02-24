#include <chrono>
#include <functional>
#include <memory>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"

using namespace std::chrono_literals;

/*
 * TODO: Create a Class named 'TFBroadcaster' that inherits from rclcpp::Node.
 * Requirements:
 * 1. The constructor should name the node "tf_broadcaster".
 * 2. Create a TransformBroadcaster.
 * 3. Create a timer that triggers every 100ms.
 * 4. In timer callback:
 * - Create a TransformStamped message
 * - Set header.stamp to current time
 * - Set header.frame_id to "world"
 * - Set child_frame_id to "robot"
 * - Calculate circular motion:
 * x = 2.0 * cos(time_seconds)
 * y = 2.0 * sin(time_seconds)
 * z = 0.0
 * - Set rotation to identity quaternion (0, 0, 0, 1)
 * - Broadcast the transform
 */

class TFBroadcaster : public rclcpp::Node
{
public:
    TFBroadcaster()
        : Node("tf_broadcaster")
    {
        // TODO: Create the transform broadcaster here
        tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

        // TODO: Create the timer here
        timer_ = this->create_wall_timer(
            100ms, std::bind(&TFBroadcaster::timer_callback, this));
    }

private:
    // TODO: Define timer_callback function here
    void timer_callback()
    {
        geometry_msgs::msg::TransformStamped t;

        t.header.stamp = this->get_clock()->now();
        t.header.frame_id = "world";
        t.child_frame_id = "robot";

        double time_seconds = this->get_clock()->now().seconds();

        t.transform.translation.x = 2.0 * cos(time_seconds);
        t.transform.translation.y = 2.0 * sin(time_seconds);
        t.transform.translation.z = 0.0;

        t.transform.rotation.x = 0.0;
        t.transform.rotation.y = 0.0;
        t.transform.rotation.z = 0.0;
        t.transform.rotation.w = 1.0;

        tf_broadcaster_->sendTransform(t);
    }

    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TFBroadcaster>());
    rclcpp::shutdown();
    return 0;
}