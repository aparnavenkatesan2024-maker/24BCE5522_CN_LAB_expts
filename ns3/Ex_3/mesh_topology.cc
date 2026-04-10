#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;
int main () {
  NodeContainer nodes;
  nodes.Create (18);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));
  for (uint32_t i = 0; i < nodes.GetN (); i++) {
    for (uint32_t j = i + 1; j < nodes.GetN (); j++) {
      if ((i + j) % 3 == 0) {   // partial mesh
        NodeContainer link;
        link.Add (nodes.Get (i));
        link.Add (nodes.Get (j));
        csma.Install (link);
      }
    }
  }

  AnimationInterface anim ("mesh.xml");
  Simulator::Stop (Seconds (5));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}

