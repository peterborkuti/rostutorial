import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class AddNumsServiceServer(Node):

    def __init__(self):
        super().__init__("add_nums_server")
        self.get_logger().info(self.get_name() + " node started")
        self.service = self.create_service(AddTwoInts, "add_nums_service", self.service_callback)

    def service_callback(self, request, response):
        response.sum = request.a + request.b
        self.get_logger().info(self.get_name() + str(request.a) + "+" + str(request.b) + "=" + str(response.sum))
        return response

def main(args=None):
    rclpy.init(args=args)
    node = AddNumsServiceServer()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
