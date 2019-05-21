// Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/string.hpp"

int main(int argc, char * argv[])
{
  // Force flush of the stdout buffer
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);

  // Configuration and Initialization
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exec;

  std::string topic("qos_durability_chatter");

  auto node = std::make_shared<rclcpp::Node>("durability_demo");

  rclcpp::QoS qos_profile(1);
  qos_profile.transient_local();  // store the message on the publisher indefinitely

  rclcpp::SubscriptionOptions sub_options;
  rclcpp::PublisherOptions pub_options;
  auto publisher = node->create_publisher<std_msgs::msg::String>(topic, qos_profile, pub_options);

  std_msgs::msg::String msg;
  msg.data = "PUBLISHER SAYS HI";
  publisher->publish(msg);

  auto subscription = node->create_subscription<std_msgs::msg::String>(
    topic,
    qos_profile,
    [](const std_msgs::msg::String::SharedPtr msg) -> void
    {
      RCLCPP_INFO(rclcpp::get_logger("DurabilityDemo"),
        "Subscription received: [%s]", msg->data.c_str());
    },
    sub_options
  );
  rclcpp::spin(node);

  // Cleanup
  rclcpp::shutdown();
  return 0;

  return 0;
}
