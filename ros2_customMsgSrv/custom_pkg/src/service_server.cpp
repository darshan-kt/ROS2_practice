#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/value.hpp"                                        // CHANGE

#include <memory>

void add(const std::shared_ptr<custom_interfaces::srv::Value::Request> request,     // CHANGE
          std::shared_ptr<custom_interfaces::srv::Value::Response>       response)  // CHANGE
{
  response->val = request->a + request->b;                                      // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",  // CHANGE
                request->a, request->b);                                         // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->val);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");   // CHANGE

  rclcpp::Service<custom_interfaces::srv::Value>::SharedPtr service =               // CHANGE
    node->create_service<custom_interfaces::srv::Value>("add_two_ints",  &add);   // CHANGE

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");                     // CHANGE

  rclcpp::spin(node);
  rclcpp::shutdown();
}