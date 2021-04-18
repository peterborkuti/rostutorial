#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class MyFirstPublisher : public rclcpp::Node
{
public:
    MyFirstPublisher() : Node("cpp_publisher"), counter_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello from %s", this->get_name());

        publisher = this->create_publisher<example_interfaces::msg::String>("string_messages", 10);

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&MyFirstPublisher::timerCallback, this));
    }

private:
    
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher;
    void timerCallback()
    {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
        auto data = example_interfaces::msg::String();
        data.data = std::string("Hello ") + std::to_string(counter_);
        publisher->publish(data);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyFirstPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
