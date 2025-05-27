#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("starter"), "This is a placeholder node.");
    rclcpp::shutdown();
    return 0;
}
