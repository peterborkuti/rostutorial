#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddNumsServiceServer : public rclcpp::Node
{
public:
    AddNumsServiceServer() : Node("add_nums_service_server")
    {
        RCLCPP_INFO(this->get_logger(), "Hello from %s", this->get_name());

        service = this->create_service<example_interfaces::srv::AddTwoInts>(
            "add_nums_service",
            std::bind(&AddNumsServiceServer::service_callback, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service;

    void service_callback(
        const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
        const example_interfaces::srv::AddTwoInts::Response::SharedPtr response) {
 
        RCLCPP_INFO(this->get_logger(), "Got %d, %d", request->a, request->b);

        response->sum = request->a + request->b;
    }


};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddNumsServiceServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
