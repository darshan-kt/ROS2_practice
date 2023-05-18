#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class MyNode(Node):               #Creating class with refernce to Node class

    def __init__(self):
        super().__init__("py_test")
        self.counter = 0
        self.get_logger().info("Hello ROS 2")
        self.create_timer(0.5, self.timer_callback)   #This function calls the timer_callback every 0.5 sec

    def timer_callback(self):
        self.counter +=1
        self.get_logger().info("Hello " + str(self.counter))

def main(args= None):
    rclpy.init(args= args)
    node = MyNode()           #creating node object by calling class
    rclpy.spin(node)          #The above class object will be keep alive untill press ctrl C
    rclpy.shutdown()

if __name__ == "__main__":
    main()