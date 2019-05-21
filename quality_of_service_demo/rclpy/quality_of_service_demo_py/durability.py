import rclpy
from rclpy.node import Node
from rclpy.qos import QoSDurabilityPolicy
from rclpy.qos import QoSProfile

from std_msgs.msg import String


def main(args=None):
    rclpy.init(args=args)
    topic = 'qos_durability_chatter'

    node = Node('durability_demo')
    qos_profile = QoSProfile(
        depth=1,
        durability=QoSDurabilityPolicy.RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL)
    publisher = node.create_publisher(String, topic, qos_profile)

    message = String()
    message.data = 'PUBLISHER SAYS HI'
    publisher.publish(message)

    subscription = node.create_subscription(  # noqa: F841
        String, topic,
        lambda msg: print('Subscription received: [{}]'.format(msg.data)),
        qos_profile)

    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
