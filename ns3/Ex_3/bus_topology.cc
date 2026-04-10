#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;
int main(int argc, char *argv[])
{
    uint32_t nNodes = 16;
    NodeContainer nodes;
    nodes.Create(nNodes);
    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    csma.SetChannelAttribute("Delay", TimeValue(MicroSeconds(10)));

    NetDeviceContainer devices;
    devices = csma.Install(nodes);
    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces;
    interfaces = address.Assign(devices);

    AnimationInterface anim("bus.xml");

    for (uint32_t i = 0; i < nNodes; i++)
    {
        anim.SetConstantPosition(nodes.Get(i), 50 + i * 40, 200);
    }

    Simulator::Stop(Seconds(10));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}

