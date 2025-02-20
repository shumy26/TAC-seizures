#include "calculatetcc_node.h"

CalculateTTC::CalculateTTC(const std::string &name, const BT::NodeConfiguration &config)
    : BT::SyncActionNode(name, config) {}

BT::NodeStatus CalculateTTC::tick() {
    // Create the message
    std::string message = "The mission will be finished in x minutes";
    return BT::NodeStatus::SUCCESS;
}