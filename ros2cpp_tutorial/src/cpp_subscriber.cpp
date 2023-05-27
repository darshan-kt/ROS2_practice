    #include "rclcpp/rclcpp.hpp"
    #include "std_msgs/msg/string.hpp"
     
    class SmartphoneNode : public rclcpp::Node // MODIFY NAME
    {
    public:
        SmartphoneNode() : Node("smartphone") // MODIFY NAME
        {
            //Initialise a subscriber  (2)
            subscriber_ = this->create_subscription<std_msgs::msg::String>("robot_news", 10,
                                                    std::bind(&SmartphoneNode::calllbackRobotNews, this, std::placeholders::_1));

            //Initialize a logger just for debugging
            RCLCPP_INFO(this->get_logger(), "Robot News Station has been started");
        }
     
    private:
        //create callback initializer (3)
        void calllbackRobotNews(const std_msgs::msg::String::SharedPtr msg)
        {
            RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
        }

        //Declare subscriber object (1)
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;

    };
     
    int main(int argc, char **argv)
    {
        rclcpp::init(argc, argv);
        auto node = std::make_shared<SmartphoneNode>(); // MODIFY NAME
        rclcpp::spin(node);
        rclcpp::shutdown();
        return 0;
    }