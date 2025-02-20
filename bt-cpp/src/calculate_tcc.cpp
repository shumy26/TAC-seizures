#include <behaviortree_cpp_v3/action_node.h>
#include <string>

class CalculateTTC : public BT::SyncActionNode {
public:
    CalculateTTC(const std::string &name, const BT::NodeConfiguration &config)
        : BT::SyncActionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return { BT::OutputPort<std::string>("ttc") };
    }

    BT::NodeStatus tick() override {
        // Create the message
        std::string message = "The mission will be finished in x minutes";

        // Set the output port
        setOutput("ttc", message);

        return BT::NodeStatus::SUCCESS;
    }
};