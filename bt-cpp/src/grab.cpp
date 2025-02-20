class Grab : public BT::SyncActionNode
{
public:
  ApproachObject(const std::string& name) :
      BT::SyncActionNode(name, {})
  {}


  BT::NodeStatus tick() override
  {
    std::cout << "Grabbed Equipment" << std::endl;
    return BT::NodeStatus::SUCCESS;
  }
};