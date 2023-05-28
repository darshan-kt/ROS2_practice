cmake_minimum_required(VERSION 3.5)
project(assignment_pkg)

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
add_executable(numPub src/num_publisher.cpp)
add_executable(numSubPub src/numSubPub.cpp)

# 2. Add target dependecies for executable

ament_target_dependencies(numPub rclcpp std_msgs)
ament_target_dependencies(numSubPub rclcpp std_msgs)

# 3. Add executable storing target destination
install(TARGETS
        numPub
        numSubPub
        DESTINATION lib/${PROJECT_NAME}
        )

ament_package()
