#ifndef HAS_ALL_ITEMS_NODE_H
#define HAS_ALL_ITEMS_NODE_H

#include <behaviortree_cpp_v3/condition_node.h>
#include <rclcpp/rclcpp.hpp>
#include <string>

class HasAllItems : public BT::ConditionNode {
public:
    HasAllItems(const std::string &name, const BT::NodeConfiguration &config);

    BT::NodeStatus tick() override;

    static BT::PortsList providedPorts() {
        return {};
    }
};

#endif // HAS_ALL_ITEMS_NODE_H