from launch import LaunchDescription
from launch_ros.actions import Node      #Need import Node for create nodes 

def generate_launch_description():   #Inside this create launchable nodes
    ld = LaunchDescription()          #Create objects for launchDescription

    ros2py_node = Node(
        package = "ros2py_tutorials",
        node_executable = "testpy_node" 
    )

    ros2cpp_node = Node(
        package = "ros2cpp_tutorial",
        node_executable = "cpp_node"
    )

    ld.add_action(ros2py_node)        #Adding node objects for LaunchDescription object
    ld.add_action(ros2cpp_node)

    return ld                         #Finally return LaunchDescription object