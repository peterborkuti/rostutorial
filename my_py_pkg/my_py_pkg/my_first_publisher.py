import rclpy
from rclpy.node import Node
from example_interfaces.msg import String


class MyFirstPublisher(Node):

    def __init__(self):
        super().__init__("py_publisher")
        self.counter_ = 0
        self.publisher = self.create_publisher(String, "string_messages", 10)
        self.get_logger().info("Hello ROS2")
        self.create_timer(0.5, self.timer_callback)

    def timer_callback(self):
        self.counter_ += 1
        data = String()
        data.data = "Hello " + str(self.counter_)
        self.publisher.publish(data)
        self.get_logger().info("Hello " + str(self.counter_))


def main(args=None):
    rclpy.init(args=args)
    node = MyFirstPublisher()
    
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
