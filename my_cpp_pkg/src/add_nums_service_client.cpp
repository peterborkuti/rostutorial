#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddNumsServiceClient : public rclcpp::Node
{
public:
    AddNumsServiceClient() : Node("add_nums_service_client")
    {
        RCLCPP_INFO(this->get_logger(), "Hello from %s", this->get_name());
        thread = std::thread(std::bind(&AddNumsServiceClient::call_service, this, 3, 5));
    }

private:
    std::thread thread;

    void call_service(const int a, const int b) {
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_nums_service");

        while (!client->wait_for_service(std::chrono::seconds(1))) {
                    RCLCPP_INFO(this->get_logger(), "Waiting for service");
        };

        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;
        auto future = client->async_send_request(request);

        RCLCPP_INFO(this->get_logger(), "Request sent");

        try {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "Response got");
            RCLCPP_INFO(this->get_logger(), "Got: %d", response->sum);
        }
        catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Service call fiailed");
        }

        RCLCPP_INFO(this->get_logger(), "call service done");
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddNumsServiceClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
