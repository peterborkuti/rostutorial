import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts
from functools import partial

class AddNumsServiceClientOOP(Node):
    def __init__(self):
        super().__init__("add_nums_client_oop")
        self.get_logger().info(self.get_name() + " node started")
        self.client = self.create_client(AddTwoInts, "add_nums_service")
        self.call_service(1,5)


    def call_service(self, a, b):
        while not self.client.wait_for_service(1):
            self.get_logger().info("waiting for " + self.client.srv_name)

        request = AddTwoInts.Request()
        request.a = a
        request.b = b

        future = self.client.call_async(request)
        future.add_done_callback(partial(self.done_callback, a=a, b=b))


    def done_callback(self, future, a, b):
        try:
            response = future.result()
            self.get_logger().info("Got " + str(response.sum))
        except Exception as e:
            self.get.get_logger().error("Service error %r" % (e,))


def main(args=None):
    rclpy.init(args=args)
    node = AddNumsServiceClientOOP()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
