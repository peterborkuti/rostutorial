cmake_minimum_required(VERSION 3.5)
project(my_cpp_pkg)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

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
find_package(example_interfaces REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(cpp_node src/my_first_node.cpp)
ament_target_dependencies(cpp_node rclcpp)

add_executable(cpp_publisher src/my_first_publisher.cpp)
ament_target_dependencies(cpp_publisher rclcpp example_interfaces)

add_executable(cpp_subscriber src/my_first_subscriber.cpp)
ament_target_dependencies(cpp_subscriber rclcpp example_interfaces)

add_executable(number_counter src/number_counter.cpp)
ament_target_dependencies(number_counter rclcpp example_interfaces)

add_executable(number_publisher src/number_publisher.cpp)
ament_target_dependencies(number_publisher rclcpp example_interfaces)

add_executable(add_nums_service src/add_nums_service_server.cpp)
ament_target_dependencies(add_nums_service rclcpp example_interfaces)

add_executable(add_nums_client src/add_nums_service_client.cpp)
ament_target_dependencies(add_nums_client rclcpp example_interfaces)

install(TARGETS 
  cpp_node
  cpp_publisher
  cpp_subscriber
  number_counter
  number_publisher
  add_nums_service
  add_nums_client
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
