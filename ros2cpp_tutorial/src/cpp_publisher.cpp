#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


class RobotNewsStationNode : public rclcpp::Node         //Inheriting Node class
{
public:
    RobotNewsStationNode() : Node("robot_news_station") // MODIFY NAME
    {
        //Initialise a publisher  (2)
        publisher_ = this->create_publisher<std_msgs::msg::String>("robot_news", 10);

        //Initialize timer  (5)
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), 
                                         std::bind(&RobotNewsStationNode::publishNews, this));  

        //Initialize a logger just for debugging
        RCLCPP_INFO(this->get_logger(), "Robot News Station has been started");

    }
     
private:
    //Create function to publish data (3)
    void publishNews()
    {
        auto msg = std_msgs::msg::String();
        msg.data =  std::string("Hi this is robot news ");
        // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg.data.c_str());
        publisher_->publish(msg);
    }

    //Declare publisher here      (1)
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    //Calling the publisher frequently by declaring timer (4)
    rclcpp::TimerBase::SharedPtr timer_;
};
     
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);              //This initializes ros communication
    auto node = std::make_shared<RobotNewsStationNode>(); // creates node object using object type RobotNewsStationNode  [so write a class of RobotNewsStationNode]
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}