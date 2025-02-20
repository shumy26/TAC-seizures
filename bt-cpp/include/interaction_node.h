#ifndef INTERACTION_NODE_H
#define INTERACTION_NODE_H

#include <behaviortree_cpp_v3/action_node.h>
#include <rclcpp/rclcpp.hpp>
#include <string>

class Interaction : public BT::SyncActionNode {
public:
    Interaction(const std::string &name, const BT::NodeConfiguration &config);
    BT::NodeStatus tick() override;
};

#endif // INTERACTION_NODE_H