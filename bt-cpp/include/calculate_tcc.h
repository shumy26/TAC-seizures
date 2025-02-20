#ifndef CALCULATE_TCC_H
#define CALCULATE_TCC_H

#include <behaviortree_cpp_v3/action_node.h>
#include <string>

class CalculateTTC : public BT::SyncActionNode {
public:
    CalculateTTC(const std::string &name, const BT::NodeConfiguration &config);
    BT::NodeStatus tick() override;
};

#endif // CALCULATE_TCC_H