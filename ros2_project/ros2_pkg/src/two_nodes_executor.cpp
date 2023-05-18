#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode()
  : Node("publisher_node")
  {
    publisher_ = create_publisher<std_msgs::msg::Int32>("int_topic", 10);
    timer_ = create_wall_timer(
      500ms, std::bind(&PublisherNode::timer_callback, this));
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

class SubscriberNode : public rclcpp::Node
{
public:
  SubscriberNode()
  : Node("subscriber_node")
  {
    subscriber_ = create_subscription<std_msgs::msg::Int32>(
      "int_topic", 10,
      std::bind(&SubscriberNode::callback, this, _1));
  }

  void callback(const std_msgs::msg::Int32::SharedPtr msg)
  {
    RCLCPP_INFO(get_logger(), "Hello %d", msg->data);
  }

private:
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node_pub = std::make_shared<PublisherNode>();
  auto node_sub = std::make_shared<SubscriberNode>();

  rclcpp::executors::SingleThreadedExecutor executor;                  //Achieved by exucutor concept. Executor is an object to which nodes are added to execute them together.
  // rclcpp::executors::MultiThreadedExecutor executor(rclcpp::executor::ExecutorArgs(), 8);    //Another way using multithread executor with using eight threads to optimize the processor capabilities
  executor.add_node(node_pub);
  executor.add_node(node_sub);

  executor.spin();

  rclcpp::shutdown();
  return 0;
}
