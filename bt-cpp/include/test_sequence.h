#ifndef TestSequence_NODE_H
#define TestSequence_NODE_H

#include <behaviortree_cpp_v3/action_node.h>
#include <rclcpp/rclcpp.hpp>
#include <string>

class TestSequence : public BT::SyncActionNode {
public:
    TestSequence(const std::string &name, const BT::NodeConfiguration &config);
    BT::NodeStatus tick() override;
};

#endif // TestSequence_NODE_H