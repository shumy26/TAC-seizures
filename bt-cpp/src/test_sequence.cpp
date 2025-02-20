#include "test_sequence.h"

TestSequence::TestSequence(const std::string &name, const BT::NodeConfiguration &config)
    : BT::SyncActionNode(name, config) {}

BT::NodeStatus TestSequence::tick() {
    // Implementation of the tick function
    std::cout << "Tested" << std::endl;
    return BT::NodeStatus::SUCCESS;
}