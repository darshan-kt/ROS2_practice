#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/value.hpp"                                       // CHANGE

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 3) { // CHANGE
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");      // CHANGE
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");  // CHANGE
  rclcpp::Client<custom_interfaces::srv::Value>::SharedPtr client =                // CHANGE
    node->create_client<custom_interfaces::srv::Value>("add_two_ints");          // CHANGE

  auto request = std::make_shared<custom_interfaces::srv::Value::Request>();       // CHANGE
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);                                                             // CHANGE

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::executor::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Value: %ld", result.get()->val);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");    // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}