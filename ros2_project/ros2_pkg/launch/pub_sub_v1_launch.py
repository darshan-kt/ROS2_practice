from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    pub_cmd = Node(package="ros2_pkg", node_executable="publisher_node", output="screen")
    sub_cmd = Node(package="ros2_pkg", node_executable="subscriber_node", output="screen")

    ld = LaunchDescription()
    ld.add_action(pub_cmd)
    ld.add_action(sub_cmd)

    return ld

#Note: If you're using ros2 foxy, then replace node_executable by executable
