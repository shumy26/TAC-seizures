#include "interaction_node.h"

Interaction::Interaction(const std::string &name, const BT::NodeConfiguration &config)
    : BT::SyncActionNode(name, config) {}

BT::NodeStatus Interaction::tick() {
    // Implementation of the tick function
    std::cout << "Interacted" << std::endl;
    return BT::NodeStatus::SUCCESS;
}