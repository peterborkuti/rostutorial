#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int16.hpp"

class NumberPublisher : public rclcpp::Node
{
public:
    NumberPublisher() : Node("number_publisher")
    {
        RCLCPP_INFO(this->get_logger(), "Hello from %s", this->get_name());

        publisher = this->create_publisher<example_interfaces::msg::Int16>("numbers", 10);

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&NumberPublisher::timerCallback, this));
    }

private:
    
    rclcpp::Publisher<example_interfaces::msg::Int16>::SharedPtr publisher;
    void timerCallback()
    {
        auto data = example_interfaces::msg::Int16();
        data.data = 3;
        publisher->publish(data);
    }

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
