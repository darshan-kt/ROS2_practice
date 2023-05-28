#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

class NumberCounterNode : public rclcpp::Node
{
public:
    NumberCounterNode() : Node("number_counter")
    {
        counter_publisher_ = this->create_publisher<std_msgs::msg::Int64>("number_count", 10);
        number_subscriber_ = this->create_subscription<std_msgs::msg::Int64>(
            "number", 10, std::bind(&NumberCounterNode::callbackNumber, this, std::placeholders::_1));
    }

private:
    void callbackNumber(const std_msgs::msg::Int64::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "%d", msg->data);       //If you put %s instead of %d this program will unexpectedly get stop!

        counter_ += msg->data;
        auto newMsg = std_msgs::msg::Int64();
        newMsg.data = counter_;
        counter_publisher_->publish(newMsg);
        
    }

    int counter_ = 0;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr counter_publisher_;
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr number_subscriber_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
