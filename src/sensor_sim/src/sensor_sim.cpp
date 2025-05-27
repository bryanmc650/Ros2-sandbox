#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include <random>

class SensorSimNode : public rclcpp::Node {
public:
    SensorSimNode() : Node("sensor_sim") {
        imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>("imu", 10);
        gps_pub_ = this->create_publisher<sensor_msgs::msg::NavSatFix>("gps", 10);

        timer_ = this->create_wall_timer(std::chrono::milliseconds(100), [this]() {
            publish_fake_imu();
            publish_fake_gps();
        });
    }

private:
    void publish_fake_imu() {
        sensor_msgs::msg::Imu imu_msg;
        imu_msg.header.stamp = now();
        imu_msg.header.frame_id = "imu_link";

        imu_msg.linear_acceleration.x = noise(gen);
        imu_msg.linear_acceleration.y = noise(gen);
        imu_msg.linear_acceleration.z = 9.81 + noise(gen);  // gravity + noise

        imu_pub_->publish(imu_msg);
    }

    void publish_fake_gps() {
        sensor_msgs::msg::NavSatFix gps_msg;
        gps_msg.header.stamp = now();
        gps_msg.header.frame_id = "gps_link";

        gps_msg.latitude = 53.0 + noise(gen) * 0.0001;
        gps_msg.longitude = -6.0 + noise(gen) * 0.0001;
        gps_msg.altitude = 100.0 + noise(gen);

        gps_pub_->publish(gps_msg);
    }

    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
    rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr gps_pub_;
    rclcpp::TimerBase::SharedPtr timer_;

    std::default_random_engine gen;
    std::normal_distribution<double> noise{0.0, 0.05};
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorSimNode>());
    rclcpp::shutdown();
    return 0;
}
