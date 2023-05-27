cmake_minimum_required(VERSION 3.5)
project(ros2cpp_tutorial)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

find_package(std_msgs REQUIRED)

# 1. Add the executables
add_executable(cpp_node src/first_cpp_node.cpp)
add_executable(cpp_node_class src/cpp_class.cpp)
add_executable(publisher_node src/cpp_publisher.cpp)
add_executable(subscriber_node src/cpp_subscriber.cpp)

# 2. Add target dependecies for executable
ament_target_dependencies(cpp_node rclcpp)
ament_target_dependencies(cpp_node_class rclcpp)
ament_target_dependencies(publisher_node rclcpp std_msgs)
ament_target_dependencies(subscriber_node rclcpp std_msgs)

# 3. Add executable storing target destination
install(TARGETS
        cpp_node
        cpp_node_class
        publisher_node
        subscriber_node
        DESTINATION lib/${PROJECT_NAME}
        )

ament_package()
