#include "has_all_items.h"

HasAllItems::HasAllItems(const std::string &name, const BT::NodeConfiguration &config)
    : BT::ConditionNode(name, config) {}

BT::NodeStatus HasAllItems::tick() {
    return BT::NodeStatus::SUCCESS;
}