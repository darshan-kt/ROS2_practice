#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class PublisherNode : public rclcpp::Node
{
  public:
  PublisherNode() : Node("publisher_node")
  {
    publisher_ = create_publisher<std_msgs::msg::Int32>("int_topic", 10);
    timer_ = create_wall_timer(500ms, std::bind(&PublisherNode::timer_callback, this));
  }

  void timer_callback()
  {
    message_.data += 1;
    publisher_->publish(message_);
  }

  private:
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std_msgs::msg::Int32 message_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PublisherNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}



// using namespace std::chrono_literals;

// int main(int argc, char * argv[])
// {
//     rclcpp::init(argc, argv);

//     auto node = rclcpp::Node::make_shared("publisher_node");
//     auto publisher = node->create_publisher<std_msgs::msg::Int32>("int_topic", 10);
//     std_msgs::msg::Int32 message;
//     message.data = 0;

//     rclcpp::Rate loop_rate(500ms);
//     while (rclcpp::ok())
//     {
//         message.data +=1;
//         publisher->publish(message);

//         rclcpp::spin_some(node);
//         loop_rate.sleep();
//     }

//     rclcpp::shutdown();
//     return 0;
// }
