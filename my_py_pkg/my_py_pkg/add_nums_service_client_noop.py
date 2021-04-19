import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

def main(args=None):
    rclpy.init(args=args)
    node = Node("add_nums_client")
    client = node.create_client(AddTwoInts, "add_nums_service")
    while not client.wait_for_service(1):
        node.get_logger().info("waiting for " + client.srv_name)
    request = AddTwoInts.Request()
    request.a = 1
    request.b = 2

    future = client.call_async(request)

    rclpy.spin_until_future_complete(node, future)

    try:
        response = future.result()
        node.get_logger().info("Got " + str(response.sum))
    except Exception as e:
        node.get.get_logger().error("Service error %r" % (e,))


    rclpy.shutdown()


if __name__ == "__main__":
    main()
