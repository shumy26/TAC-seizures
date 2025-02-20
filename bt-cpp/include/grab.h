#ifndef GRAB_H
#define GRAB_H

#include <behaviortree_cpp_v3/action_node.h>
#include <rclcpp/rclcpp.hpp>
#include <string>

class Grab : public BT::SyncActionNode {
public:
    explicit Grab(const std::string &name, const BT::NodeConfiguration &config);
    BT::NodeStatus tick() override;
};

#endif // GRAB_H