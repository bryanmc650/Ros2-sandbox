#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"

class FusionNode : public rclcpp::Node {
public:
    FusionNode() : Node("sensor_fusion_core") {
        imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "imu", 10, [this](const sensor_msgs::msg::Imu::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), "Received IMU accel: %.2f", msg->linear_acceleration.z);
            });

        gps_sub_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(
            "gps", 10, [this](const sensor_msgs::msg::NavSatFix::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), "Received GPS lat: %.6f", msg->latitude);
            });
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_sub_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FusionNode>());
    rclcpp::shutdown();
    return 0;
}
