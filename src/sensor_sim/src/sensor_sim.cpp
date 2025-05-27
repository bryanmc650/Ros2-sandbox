#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"  // for ground truth

#include <random>

class SensorSimNode : public rclcpp::Node {
public:
    SensorSimNode() : Node("sensor_sim") {
        imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>("imu", 10);
        gps_pub_ = this->create_publisher<sensor_msgs::msg::NavSatFix>("gps", 10);
        truth_pub_ = this->create_publisher<geometry_msgs::msg::PointStamped>("ground_truth", 10);

        accel_ = 0.5; // constant acceleration in m/s²
        velocity_ = 0.0;
        position_ = 0.0;
        last_time_ = now();

        timer_ = this->create_wall_timer(std::chrono::milliseconds(100), [this]() {
            simulate_motion();
            publish_ground_truth();
            publish_noisy_imu();
            publish_noisy_gps();
        });
    }

private:
    void simulate_motion() {
        rclcpp::Time current_time = now();
        double dt = (current_time - last_time_).seconds();
        last_time_ = current_time;

        velocity_ += accel_ * dt;
        position_ += velocity_ * dt + 0.5 * accel_ * dt * dt;
    }

    void publish_ground_truth() {
        geometry_msgs::msg::PointStamped msg;
        msg.header.stamp = now();
        msg.header.frame_id = "world";
        msg.point.x = position_;
        msg.point.y = velocity_;
        msg.point.z = accel_;
        truth_pub_->publish(msg);
    }

    void publish_noisy_imu() {
        sensor_msgs::msg::Imu imu_msg;
        imu_msg.header.stamp = now();
        imu_msg.header.frame_id = "imu_link";
        imu_msg.linear_acceleration.x = accel_ + noise_(gen_);
        imu_pub_->publish(imu_msg);
    }

    void publish_noisy_gps() {
        sensor_msgs::msg::NavSatFix gps_msg;
        gps_msg.header.stamp = now();
        gps_msg.header.frame_id = "gps_link";
        gps_msg.latitude = 53.0 + (position_ + gps_noise_(gen_)) * 1e-5;  // fake lat offset
        gps_msg.longitude = -6.0; // fixed
        gps_msg.altitude = 100.0;
        gps_pub_->publish(gps_msg);
    }

    // Publishers
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
    rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr gps_pub_;
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr truth_pub_;

    // State
    double position_, velocity_, accel_;
    rclcpp::Time last_time_;

    // Timer
    rclcpp::TimerBase::SharedPtr timer_;

    // Noise generators
    std::default_random_engine gen_;
    std::normal_distribution<double> noise_{0.0, 0.2};       // IMU noise
    std::normal_distribution<double> gps_noise_{0.0, 1.0};   // GPS noise
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorSimNode>());
    rclcpp::shutdown();
    return 0;
}
