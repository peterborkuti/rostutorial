import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class AddNumsServiceServer(Node):

    def __init__(self):
        super().__init__("add_nums_server")
        self.get_logger().info(self.get_name() + " node started")
        self.service = self.create_service(AddTwoInts, "add_nums_service", self.service_callback)
        self.create_timer(0.5, self.timer_callback)

    def service_callback(self, request, response):
        response.sum = request.a + request.b
        self.get_logger().info(self.get_name() + str(request.a) + "+" + str(request.b) + "=" + str(response.sum))

    def timer_callback(self):
        self.counter_ += 1
        self.get_logger().info("Hello " + str(self.counter_))


def main(args=None):
    rclpy.init(args=args)
    node = AddNumsServiceServer()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
