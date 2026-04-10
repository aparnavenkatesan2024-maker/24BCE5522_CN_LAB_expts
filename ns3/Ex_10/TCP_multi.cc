#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include <vector>

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("UnifiedChatApp");
class ChatServerApp : public Application
{
public:
 ChatServerApp () : m_socket (0), m_port (9000) {}
 void Setup (uint16_t port) { m_port = port; }
private:
 virtual void StartApplication ()
 {
  m_socket=Socket::CreateSocket(GetNode(), TcpSocketFactory::GetTypeId());
  InetSocketAddress local = InetSocketAddress(Ipv4Address::GetAny(),
                            m_port);
  m_socket->Bind(local);
  m_socket->Listen();

  m_socket->SetAcceptCallback(
   MakeNullCallback<bool, Ptr<Socket>, const Address &>(),
   MakeCallback(&ChatServerApp::HandleAccept, this));
 }
 void HandleAccept(Ptr<Socket> socket, const Address &from)
 {
  socket->SetRecvCallback(MakeCallback(&ChatServerApp::HandleRead, this));
 }

 void HandleRead (Ptr<Socket> socket)
 {
  Ptr<Packet> packet;


  while ((packet = socket->Recv()))
  {
   uint32_t size = packet->GetSize();
   double timestamp = Simulator::Now().GetSeconds();
   std::stringstream msg;
   msg << "ACK | Received at: "
       << timestamp << "s | Size: "
       << size << " bytes";
   std::string responseString = msg.str();

   NS_LOG_UNCOND("Server processed packet");
   Ptr<Packet> responsePkt =
   Create<Packet>((uint8_t*)responseString.c_str(),
   responseString.length());
   socket->Send(responsePkt);
  }
 }
 Ptr<Socket> m_socket;
 uint16_t m_port;
};

class ChatClientApp : public Application
{
public:
 ChatClientApp () : m_socket (0) {}

 void Setup (Address address, Time interval, std::string name)
 {
  m_peer = address;
  m_interval = interval;
  m_name = name;
 }
private:
 virtual void StartApplication ()
 {
  m_socket=Socket::CreateSocket(GetNode(), TcpSocketFactory::GetTypeId());
  m_socket->Connect(m_peer);
  m_socket->SetRecvCallback(
        MakeCallback(&ChatClientApp::HandleResponse,this));
  SendChat();
 }
 void SendChat ()
 {
  std::string msg = "Hello from " + m_name;
  Ptr<Packet> p = Create<Packet>((uint8_t*)msg.c_str(), msg.length());
  m_socket->Send(p);


  Simulator::Schedule(m_interval,
  &ChatClientApp::SendChat,this);
 }
 void HandleResponse (Ptr<Socket> socket)
 {
  Ptr<Packet> packet = socket->Recv();
  std::vector<uint8_t> buf(packet->GetSize());
  packet->CopyData(buf.data(), packet->GetSize());
  std::string data =
  std::string((char*)buf.data(), packet->GetSize());
  NS_LOG_UNCOND("[" << m_name << "] Received -> " << data);
 }
 Ptr<Socket> m_socket;
 Address m_peer;
 Time m_interval;
 std::string m_name;
};

int main (int argc, char *argv[])
{
 NodeContainer nodes;
 nodes.Create (3);

 PointToPointHelper p2p;
 p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
 p2p.SetChannelAttribute("Delay", StringValue("2ms"));

 NetDeviceContainer d10 =
 p2p.Install(nodes.Get(1), nodes.Get(0));
 NetDeviceContainer d20 =
 p2p.Install(nodes.Get(2), nodes.Get(0));
 InternetStackHelper stack;
 stack.Install(nodes);

 Ipv4AddressHelper address;
 address.SetBase("10.1.1.0","255.255.255.0");
 Ipv4InterfaceContainer i10 = address.Assign(d10);
 address.SetBase("10.2.1.0","255.255.255.0");
 Ipv4InterfaceContainer i20 = address.Assign(d20);

 Ptr<ChatServerApp> server = CreateObject<ChatServerApp>();
 server->Setup(9000);
 nodes.Get(0)->AddApplication(server);
 server->SetStartTime(Seconds(1.0));
 server->SetStopTime(Seconds(15.0));


 Ptr<ChatClientApp> clientA = CreateObject<ChatClientApp>();
 clientA->Setup(
 InetSocketAddress(i10.GetAddress(1),9000),
 Seconds(3.0),
 "CLIENT_A");
 nodes.Get(1)->AddApplication(clientA);
 clientA->SetStartTime(Seconds(2.0));
 clientA->SetStopTime(Seconds(15.0));

 Ptr<ChatClientApp> clientB = CreateObject<ChatClientApp>();
 clientB->Setup(
 InetSocketAddress(i20.GetAddress(1),9000),
 Seconds(5.0),
 "CLIENT_B");
 nodes.Get(2)->AddApplication(clientB);
 clientB->SetStartTime(Seconds(2.0));
 clientB->SetStopTime(Seconds(15.0));

 NS_LOG_UNCOND("--- Starting Simulation ---");
 Simulator::Stop(Seconds(15.0));
 Simulator::Run();
 Simulator::Destroy();
 NS_LOG_UNCOND("--- Simulation Finished ---");
 return 0;
}
