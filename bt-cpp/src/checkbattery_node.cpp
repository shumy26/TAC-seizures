#include <iostream>
#include <string>
#include <behaviortree_cpp_v3/action_node.h>

class CheckBattery : public BT::SyncActionNode
{
public:
    CheckBattery(const std::string &name, const BT::NodeConfiguration &config)
        : BT::SyncActionNode(name, config) {}

    // You must override the virtual function tick()
    BT::NodeStatus tick() override
    {
        std::cout << "The robot has x% battery left" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};