#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);    //Initialize node

    auto node = std::make_shared<rclcpp::Node>("cpp_test");  //Create node object using share_ptr with rclcpp::Node type so directly find node object from rclcpp & pass param as node_name
    RCLCPP_INFO(node->get_logger(), "Hello CPP Node");
    rclcpp::spin(node);                      //pause code here & allow node tobe alive

    rclcpp::shutdown();           //Shutdown node
    return 0;
}