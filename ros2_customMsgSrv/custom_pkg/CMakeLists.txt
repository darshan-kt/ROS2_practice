cmake_minimum_required(VERSION 3.5)
project(custom_pkg)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

#Custom message changes
find_package(rclcpp REQUIRED)
find_package(custom_interfaces REQUIRED)                      # CHANGE

add_executable(talker src/publisher.cpp)
ament_target_dependencies(talker rclcpp custom_interfaces)    # CHANGE 

add_executable(listener src/subscriber.cpp)
ament_target_dependencies(listener rclcpp custom_interfaces)  # CHANGE

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})


#Custom service
add_executable(server src/service_server.cpp)
ament_target_dependencies(server
  rclcpp custom_interfaces)                      # CHANGE

add_executable(client src/service_client.cpp)
ament_target_dependencies(client
  rclcpp custom_interfaces)                      # CHANGE

install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME})


ament_package()
