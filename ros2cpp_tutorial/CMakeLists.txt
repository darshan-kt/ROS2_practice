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

# 1. Add the executables
add_executable(cpp_node src/first_cpp_node.cpp)
add_executable(cpp_node_class src/cpp_class.cpp)

# 2. Add target dependecies for executable
ament_target_dependencies(cpp_node rclcpp)
ament_target_dependencies(cpp_node_class rclcpp)

# 3. Add executable storing target destination
install(TARGETS
        cpp_node
        DESTINATION lib/${PROJECT_NAME}
        )
install(TARGETS
        cpp_node_class
        DESTINATION lib/${PROJECT_NAME}
        )


ament_package()
