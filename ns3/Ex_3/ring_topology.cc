#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;
int main () {
  NodeContainer nodes;
  nodes.Create (16);
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));
  for (uint32_t i = 0; i < nodes.GetN (); i++) {
    NodeContainer pair;
    pair.Add (nodes.Get (i));
    pair.Add (nodes.Get ((i + 1) % nodes.GetN ()));
    csma.Install (pair);
  }

  AnimationInterface anim ("ring.xml");
  Simulator::Stop (Seconds (5));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
