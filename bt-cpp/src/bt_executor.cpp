#include "bt_executor.h"
#include "publisher_node.cpp"
#include "subscriber_node.cpp"
#include "gotopose_node.cpp" // Include the GoToPose header file
#include "calculatetcc_node.cpp"
#include "checkbattery_node.cpp"
#include "grab.cpp"
#include "interaction_node.cpp"
#include "has_all_items_node.cpp"
#include "test_sequence.cpp"

BTExecutor::BTExecutor(const std::string &node_name): rclcpp::Node(node_name) {
    this->declare_parameter("bt", rclcpp::PARAMETER_STRING);
    this->declare_parameter("tick_rate_ms", rclcpp::PARAMETER_INTEGER);
    RCLCPP_INFO(get_logger(), "Started BT Executor");
}

void BTExecutor::setup(){
    RCLCPP_INFO(get_logger(), "Started BT Setup");
    create_behavior_tree();
    RCLCPP_INFO(get_logger(), "Created BT Successfully");

    rclcpp::Parameter int_param = this->get_parameter("tick_rate_ms");
    int tick_rate_ms = int_param.as_int();
    auto timer_period = std::chrono::duration<int, std::ratio<1, 1000>>(tick_rate_ms);
    timer_ = this->create_wall_timer(
        timer_period,
        std::bind(&BTExecutor::update_behavior_tree, this));

    rclcpp::spin(shared_from_this());
}

void BTExecutor::halt_behavior_tree(){
    timer_->cancel();
    rclcpp::shutdown();
}

void BTExecutor::update_behavior_tree()
{
    BT::NodeStatus tree_status = tree_.tickRoot();
    if (tree_status == BT::NodeStatus::FAILURE){
        RCLCPP_INFO(get_logger(), "BT Ended with FAILURE");
        halt_behavior_tree();
    } else if (tree_status == BT::NodeStatus::SUCCESS){
        RCLCPP_INFO(get_logger(), "BT Ended with SUCCESS");
        halt_behavior_tree();
    }
}

void BTExecutor::register_nav2_plugins(){
    const std::string plugins_path = ament_index_cpp::get_package_share_directory("./") + "/behavior_trees/plugins.txt";
    std::ifstream plugin_file;
    plugin_file.open(plugins_path);

    BT::SharedLibrary loader;

    if (plugin_file.is_open())
        for(std::string plugin; std::getline(plugin_file, plugin);)
            factory_.registerFromPlugin(loader.getOSName(plugin));

    plugin_file.close();
}

void BTExecutor::create_behavior_tree(){
    rclcpp::Parameter str_param = this->get_parameter("bt");
    std::string tree_xml = str_param.as_string();

    // Registering Custom BT Nodes
    RCLCPP_INFO(get_logger(), "Registering Nodes");
    BT::NodeBuilder builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<PublisherNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<PublisherNode>("Publisher", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<SubscriberNode>(name, config, shared_from_this());
    };
    factory_.registerBuilder<SubscriberNode>("Subscriber", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<GoToPose>(name, config, shared_from_this());
    };
    factory_.registerBuilder<GoToPose>("GoToPose", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<CalculateTTC>(name, config);
    };
    factory_.registerBuilder<CalculateTTC>("CalculateTTC", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<CheckBattery>(name, config, shared_from_this());
    };
    factory_.registerBuilder<CheckBattery>("CheckBattery", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<Grab>(name, config);
    };
    factory_.registerBuilder<Grab>("Grab", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<Interaction>(name, config);
    };
    factory_.registerBuilder<Interaction>("Interaction", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<HasAllItems>(name, config);
    };
    factory_.registerBuilder<HasAllItems>("HasAllItems", builder);

    builder = [=](const std::string &name, const BT::NodeConfiguration &config){
        return std::make_unique<TestSequence>(name, config);
    };
    factory_.registerBuilder<TestSequence>("TestSequence", builder);

    // Registering nav2 nodes
    RCLCPP_INFO(get_logger(), "Registering Nav2 Plugins");
    register_nav2_plugins();

    // Creating tree from xml
    RCLCPP_INFO(get_logger(), "Creating Tree %s", tree_xml.c_str());
    tree_ = factory_.createTreeFromFile(tree_xml);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto executor = std::make_shared<BTExecutor>("bt_executor");

    // Set the 'bt' parameter before calling setup
    executor->set_parameter(rclcpp::Parameter("bt", "./behavior_trees/bt.xml"));
    executor->set_parameter(rclcpp::Parameter("tick_rate_ms", 1000));

    executor->setup();
    rclcpp::shutdown();
    return 0;
}