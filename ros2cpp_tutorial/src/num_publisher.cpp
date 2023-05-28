    /*
    You’ll create 2 nodes from scratch. In the first one you’ll have 1 publisher, and in the second one, 1 publisher & 1 subscriber.

    The number_publisher node publishes a number (always the same) on the “/number” topic, with the existing type std_msgs/msg/Int64.

    The number_counter node subscribes to the “/number” topic. It keeps a counter variable. Every time a new number is received, it’s added to the counter.
    The node also has a publisher on the “/number_count” topic. When the counter is updated, the publisher directly publishes the new value on the topic.
    */
    
    
    #include "rclcpp/rclcpp.hpp"
    #include "std_msgs/msg/int64.hpp"

    using namespace std;

    class NumPubNode : public rclcpp::Node // MODIFY NAME
    {
    public:
        NumPubNode() : Node("number_publisher") // MODIFY NAME
        {
            publisher_ = this->create_publisher<std_msgs::msg::Int64>("number", 10);
            
            timer_ = this->create_wall_timer(std::chrono::milliseconds(1000), 
                                         std::bind(&NumPubNode::numPublish, this));  
            RCLCPP_INFO(this->get_logger(), "Num publisher initialised!");
        }
     
    private:
        void numPublish()
        {
            auto msg = std_msgs::msg::Int64();
            msg.data = counter_ ;
            publisher_->publish(msg);
            // counter_ ++;
        }

        rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
        int counter_ = 222 ;  //Some dummy number
        rclcpp::TimerBase::SharedPtr timer_;

    };
     
    int main(int argc, char **argv)
    {
        rclcpp::init(argc, argv);
        auto node = std::make_shared<NumPubNode>(); 
        rclcpp::spin(node);
        rclcpp::shutdown();
        return 0;
    }