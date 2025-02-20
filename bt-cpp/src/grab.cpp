#include "grab.h"

Grab::Grab(const std::string &name, const BT::NodeConfiguration &config)
    : BT::SyncActionNode(name, config) {}

BT::NodeStatus Grab::tick() {
    // Implementation of the tick function
    std::cout<<"Grabbed"<<std::endl;
    return BT::NodeStatus::SUCCESS;
}