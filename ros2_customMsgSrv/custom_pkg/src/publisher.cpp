#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/person.hpp"                                            // CHANGE

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<custom_interfaces::msg::Person>("topic", 3);  // CHANGE
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = custom_interfaces::msg::Person();  
    message.name = "Darshan";                               // CHANGE
    message.age = 26;                                                     // CHANGE
    RCLCPP_INFO(this->get_logger(), "I am sending : '%s' '%d'", message.name.c_str(), message.age);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<custom_interfaces::msg::Person>::SharedPtr publisher_;             // CHANGE
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}