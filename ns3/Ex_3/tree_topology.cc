#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;

int main () {
  NodeContainer nodes;
  nodes.Create (15);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  uint32_t parent = 0;
  for (uint32_t i = 1; i < nodes.GetN (); i++) {
    NodeContainer link;
    link.Add (nodes.Get (parent));
    link.Add (nodes.Get (i));
    csma.Install (link);

    if (i % 2 == 0)
      parent++;
  }
  AnimationInterface anim ("tree.xml");
  anim.EnablePacketMetadata(true);
  anim.EnableIpv4RouteTracking("tree-routes.xml", Seconds(0), Seconds(5),
                                 Seconds(0.25));

  double x = 300.0, y = 50.0, gap = 80.0;
  anim.SetConstantPosition(nodes.Get(0), x, y);

  for (uint32_t i = 1; i < nodes.GetN (); i++) {
    anim.SetConstantPosition(nodes.Get(i),
      x + (i % 5) * gap,
      y + (i / 5 + 1) * gap);
  }
  Simulator::Stop (Seconds (5));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}

