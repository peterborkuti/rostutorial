import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int16


class NumberPublisher(Node):

    def __init__(self):
        super().__init__("number_publisher")
        self.get_logger().info("Hello from " + self.get_name())
        self.counter_ = 0
        self.publisher = self.create_publisher(Int16, "numbers", 10)
        self.create_timer(0.5, self.timer_callback)

    def timer_callback(self):
        self.counter_ += 1
        data = Int16()
        data.data = self.counter_
        self.publisher.publish(data)


def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisher()
    
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
