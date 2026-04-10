#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;
void ReceivePacket(Ptr<const Packet> packet, const Address &address)
{
 std::cout << "Server received "
           << packet->GetSize()
           << " bytes at "
           << Simulator::Now().GetSeconds()
           << " s" << std::endl;
}
int main(int argc, char *argv[])
{
 NodeContainer nodes;
 nodes.Create(2);
 PointToPointHelper p2p;
 p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
 p2p.SetChannelAttribute("Delay", StringValue("2ms"));
 NetDeviceContainer devices = p2p.Install(nodes);
 InternetStackHelper stack;
 stack.Install(nodes);
 Ipv4AddressHelper address;
 address.SetBase("10.1.1.0","255.255.255.0");

 Ipv4InterfaceContainer interfaces = address.Assign(devices);
 uint16_t port = 8080;
 PacketSinkHelper sink("ns3::TcpSocketFactory",
 InetSocketAddress(Ipv4Address::GetAny(), port));
 ApplicationContainer sinkApp = sink.Install(nodes.Get(1));
 sinkApp.Start(Seconds(1.0));
 sinkApp.Stop(Seconds(10.0));


 Ptr<PacketSink> sink1 = DynamicCast<PacketSink>(sinkApp.Get(0));
 sink1->TraceConnectWithoutContext("Rx", MakeCallback(&ReceivePacket));
 OnOffHelper client("ns3::TcpSocketFactory",
 InetSocketAddress(interfaces.GetAddress(1), port));

 client.SetAttribute("PacketSize", UintegerValue(1024));
 client.SetAttribute("DataRate", StringValue("1Mbps"));
 client.SetAttribute("StartTime", TimeValue(Seconds(2.0)));
 client.SetAttribute("StopTime", TimeValue(Seconds(8.0)));

 ApplicationContainer clientApp = client.Install(nodes.Get(0));
 Simulator::Stop(Seconds(10.0));
 Simulator::Run();
 Simulator::Destroy();
 return 0;
}
