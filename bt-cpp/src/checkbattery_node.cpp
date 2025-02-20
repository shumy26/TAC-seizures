#include <iostream>
#include <string>
#include <behaviortree_cpp_v3/action_node.h>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/battery_state.hpp"

class CheckBattery : public BT::StatefulActionNode
{
public:
    CheckBattery(const std::string &name, 
                 const BT::NodeConfiguration &config,
                 rclcpp::Node::SharedPtr node)
        : BT::StatefulActionNode(name, config),
          node_(node),
          battery_percentage_(0.0)
    {
        // Create subscription to battery state topic
        battery_sub_ = node_->create_subscription<sensor_msgs::msg::BatteryState>(
            "/battery_state",
            10,
            std::bind(&CheckBattery::batteryCallback, this, std::placeholders::_1)
        );
    }

    static BT::PortsList providedPorts() {
        return { BT::OutputPort<bool>("over10percent") };
    }

    BT::NodeStatus onStart() override {
        RCLCPP_INFO(node_->get_logger(), "Checking Battery Level...");
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {
        bool is_over_10 = battery_percentage_ > 10.0;
        setOutput("over10percent", is_over_10);
        return is_over_10 ? BT::NodeStatus::RUNNING : BT::NodeStatus::FAILURE;
    }

    void onHalted() override {
        RCLCPP_INFO(node_->get_logger(), "CheckBattery node halted.");
    }

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr battery_sub_;
    double battery_percentage_;

    void batteryCallback(const sensor_msgs::msg::BatteryState::SharedPtr msg)
    {
        if (msg->capacity > 0.0) {
            battery_percentage_ = (msg->charge / msg->capacity) * 100.0;
            RCLCPP_INFO(node_->get_logger(), "Battery at %.1f%%", battery_percentage_);
        } else {
            RCLCPP_WARN(node_->get_logger(), "Invalid battery capacity!");
            battery_percentage_ = 0.0;
        }
    }
};