#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/person.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<custom_interfaces::msg::Person>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const custom_interfaces::msg::Person::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%s' '%d'", msg->name.c_str(), msg->age);
    }
    rclcpp::Subscription<custom_interfaces::msg::Person>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
