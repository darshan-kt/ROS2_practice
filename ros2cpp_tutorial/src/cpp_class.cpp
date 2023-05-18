#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node            //
{
    public:
    MyNode(): Node("cpp_test")                   //Constructor will initialize the node with node name
    {
        RCLCPP_INFO(this->get_logger(), "Hello CPP Node");       //use 'this' because inside class

        timer_ = this->create_wall_timer(std::chrono::seconds(1), 
                                         std::bind(&MyNode::timerCallback, this));
    }

    private:
    //Create a timer callback
    void timerCallback()
    {
        counter_ ++;
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
    }

    rclcpp::TimerBase::SharedPtr timer_;         //This specific to ros2 gives timebase shared ptr boject
    int counter_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);    //Initialize node

    auto node = std::make_shared<MyNode>();  //Create node object using share_ptr 
    RCLCPP_INFO(node->get_logger(), "Hello CPP Node");
    rclcpp::spin(node);                      //pause code here & allow node tobe alive

    rclcpp::shutdown();           //Shutdown node
    return 0;
}