#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class MyFirstSubscriber : public rclcpp::Node
{
public:
    MyFirstSubscriber() : Node("cpp_subscriber")
    {
        RCLCPP_INFO(this->get_logger(), "Hello from %s", this->get_name());

        subscription = this->create_subscription<example_interfaces::msg::String>("string_messages", 10,
            std::bind(&MyFirstSubscriber::myCallback, this, std::placeholders::_1));
            // std::placeholders::_1 needs because the callback has one parameter. If it would have more, use _2 or _3, etc instead of _1

    }

private:
    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscription; 

    void myCallback(const example_interfaces::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
    }

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyFirstSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
