import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int16


class NumberCounter(Node):

    def __init__(self):
        super().__init__("number_counter")
        self.get_logger().info("Hello from " + self.get_name())
        self.counter_ = 0
        self.publisher = self.create_publisher(Int16, "number_counter", 10)
        self.subscription = self.create_subscription(Int16, "numbers", self.callback, 10)

    def callback(self, msg):
        self.counter_ += 1
        data = Int16()
        data.data = self.counter_
        self.publisher.publish(data)


def main(args=None):
    rclpy.init(args=args)
    node = NumberCounter()
    
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
