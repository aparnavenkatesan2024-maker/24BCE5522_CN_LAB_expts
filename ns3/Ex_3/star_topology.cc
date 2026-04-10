#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include <cmath>
using namespace ns3;
int main() {
    uint32_t numSpokes = 15; // no. of peripheral nodes here
    NodeContainer hubNode;
    hubNode.Create(1);
    NodeContainer spokeNodes;
    spokeNodes.Create(numSpokes);
    InternetStackHelper stack;
    stack.Install(hubNode);
    stack.Install(spokeNodes);
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    for (uint32_t i = 0; i < numSpokes; ++i) {
        NodeContainer link(hubNode.Get(0), spokeNodes.Get(i));
        p2p.Install(link);
    }
    AnimationInterface anim("star-topology.xml");
    anim.SetConstantPosition(hubNode.Get(0), 50.0, 50.0); //center pos.
    for (uint32_t i = 0; i < numSpokes; ++i) {
        double angle = 2.0 * M_PI * i / numSpokes;
        double x = 50.0 + 40.0 * cos(angle);
        double y = 50.0 + 40.0 * sin(angle);
        anim.SetConstantPosition(spokeNodes.Get(i), x, y);
    }
    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
