#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

def main(args=None):
    # pass
    rclpy.init(args=args)        #initialize ros2 communication
    node = Node("py_test")         # create node using rclpy.node class
    node.get_logger().info("Hello ROS2")      #get_logger() function from node class and using info func print data 
    rclpy.spin(node)              #allow the program to continue to be alive node. If subscriber present in node then calls callback whenever recieved data
    rclpy.shutdown()              #Shutdown the system when data node died by ctrl C

if __name__ == "__main__":
    main()