import rclpy
from rclpy.node import Node
from example_interfaces.msg import String


class MyFirstSubscriber(Node):

    def __init__(self):
        super().__init__("py_subscriber")
        self.create_subscription(String, "string_messages", self.subscription__callback, 10)

    def subscription__callback(self, msg):
        self.get_logger().info("Got message: " + msg.data)

def main(args=None):
    rclpy.init(args=args)
    node = MyFirstSubscriber()
    
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
