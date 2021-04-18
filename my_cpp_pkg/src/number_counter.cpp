#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int16.hpp"

class NumberCounter : public rclcpp::Node
{
public:
    NumberCounter() : Node("number_counter")
    {
        RCLCPP_INFO(this->get_logger(), "Hello from %s", this->get_name());
        counter = 0;

        subscription = this->create_subscription<example_interfaces::msg::Int16>("numbers", 10,
            std::bind(&NumberCounter::myCallback, this, std::placeholders::_1));
            // std::placeholders::_1 needs because the callback has one parameter. If it would have more, use _2 or _3, etc instead of _1

        publisher = this->create_publisher<example_interfaces::msg::Int16>("number_counter", 10);

    }

private:
    rclcpp::Subscription<example_interfaces::msg::Int16>::SharedPtr subscription;
    rclcpp::Publisher<example_interfaces::msg::Int16>::SharedPtr publisher;

    void myCallback(const example_interfaces::msg::Int16::SharedPtr msg)
    {
        counter++;
        auto data = example_interfaces::msg::Int16();
        data.data = counter;
        publisher->publish(data);
        RCLCPP_INFO(this->get_logger(), "Got number %d", msg->data);
    }

    int counter;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
