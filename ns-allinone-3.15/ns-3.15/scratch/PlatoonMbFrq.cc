#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/aodv-module.h"
#include "ns3/dsdv-module.h"
#include "ns3/idrm-module.h"
#include "ns3/dsr-module.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;

uint32_t nMANET = 7;
NS_LOG_COMPONENT_DEFINE ("5MANETS");

int main(int argc, char* argv[])
{
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  //LogComponentEnable ("AodvRoutingProtocol", LOG_LEVEL_LOGIC);
  
  
  //6 goups of nodes, Platoon1, Platoon2, Platoon3, Platoon4, Platoon5, Company
  NodeContainer Platoon1;
  NodeContainer Platoon2;
  NodeContainer Platoon3;
  NodeContainer Platoon4;
  NodeContainer Platoon5;
  NodeContainer Company;


  //7 nodes in each Platoon
  Platoon1.Create(nMANET);
  Platoon2.Create(nMANET);
  Platoon3.Create(nMANET);
  Platoon4.Create(nMANET);
  Platoon5.Create(nMANET);

  //GATEWAY and GATEWAY Candidate nodes come from 5 Platoons 
  Company.Add(Platoon1.Get(0));
  Company.Add(Platoon1.Get(1));
  Company.Add(Platoon1.Get(2));
  Company.Add(Platoon1.Get(3));
  
  Company.Add(Platoon2.Get(0));
  Company.Add(Platoon2.Get(1));
  Company.Add(Platoon2.Get(2));
  Company.Add(Platoon2.Get(3));
  
  Company.Add(Platoon3.Get(0));
  Company.Add(Platoon3.Get(1));
  Company.Add(Platoon3.Get(2));
  Company.Add(Platoon3.Get(3));
  
  Company.Add(Platoon4.Get(0));
  Company.Add(Platoon4.Get(1));
  Company.Add(Platoon4.Get(2));
  Company.Add(Platoon4.Get(3));
  
  Company.Add(Platoon5.Get(0));
  Company.Add(Platoon5.Get(1));
  Company.Add(Platoon5.Get(2));
  Company.Add(Platoon5.Get(3));

  //set nodes to 3 types
  //Type0 normal node (node 4,5,6)
  //Type1 gateway candidate (node 2,3)
  //Type2 gateway node (node 0,1)

  for(int i=0; i<=1; i++)
	{
		Platoon1.Get(i)->SetNType(2);
		Platoon2.Get(i)->SetNType(2);
		Platoon3.Get(i)->SetNType(2);
		Platoon4.Get(i)->SetNType(2);
		Platoon5.Get(i)->SetNType(2);
	}
	
  for(int i=2; i<=3; i++)
	{
		Platoon1.Get(i)->SetNType(1);
		Platoon2.Get(i)->SetNType(1);
		Platoon3.Get(i)->SetNType(1);
		Platoon4.Get(i)->SetNType(1);
		Platoon5.Get(i)->SetNType(1);
	}
	
  for(int i=4; i<=6; i++)
	{
		Platoon1.Get(i)->SetNType(0);
		Platoon2.Get(i)->SetNType(0);
		Platoon3.Get(i)->SetNType(0);
		Platoon4.Get(i)->SetNType(0);
		Platoon5.Get(i)->SetNType(0);
	}

  //phy-layer for Platoon1
  YansWifiChannelHelper P1channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper P1phy = YansWifiPhyHelper::Default ();
  P1phy.Set("ChannelNumber",UintegerValue(1)); 
  P1phy.SetChannel (P1channel.Create ());
 
  WifiHelper P1wifi = WifiHelper::Default ();
  P1wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
  //mac-layer for Platoon1
  NqosWifiMacHelper P1mac = NqosWifiMacHelper::Default ();
  P1mac.SetType ("ns3::AdhocWifiMac");
  
  
  
  //phy-layer for Platoon2
  YansWifiChannelHelper P2channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper P2phy = YansWifiPhyHelper::Default ();
  P2phy.Set("ChannelNumber",UintegerValue(2)); 
  P2phy.SetChannel (P2channel.Create ());
 
  WifiHelper P2wifi = WifiHelper::Default ();
  P2wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
  //mac-layer for Platoon2
  NqosWifiMacHelper P2mac = NqosWifiMacHelper::Default ();
  P2mac.SetType ("ns3::AdhocWifiMac");
  
  
  
  
  //phy-layer for Platoon3
  YansWifiChannelHelper P3channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper P3phy = YansWifiPhyHelper::Default ();
  P3phy.Set("ChannelNumber",UintegerValue(3)); 
  P3phy.SetChannel (P3channel.Create ());
 
  WifiHelper P3wifi = WifiHelper::Default ();
  P3wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
  //mac-layer for Platoon3
  NqosWifiMacHelper P3mac = NqosWifiMacHelper::Default ();
  P3mac.SetType ("ns3::AdhocWifiMac");
  
  
  
  
  //phy-layer for Platoon4
  YansWifiChannelHelper P4channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper P4phy = YansWifiPhyHelper::Default ();
  P4phy.Set("ChannelNumber",UintegerValue(4)); 
  P4phy.SetChannel (P4channel.Create ());
 
  WifiHelper P4wifi = WifiHelper::Default ();
  P4wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
  //mac-layer for Platoon4
  NqosWifiMacHelper P4mac = NqosWifiMacHelper::Default ();
  P4mac.SetType ("ns3::AdhocWifiMac");
  
  
  
  
  //phy-layer for Platoon5
  YansWifiChannelHelper P5channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper P5phy = YansWifiPhyHelper::Default ();
  P5phy.Set("ChannelNumber",UintegerValue(5)); 
  P5phy.SetChannel (P5channel.Create ());
 
  WifiHelper P5wifi = WifiHelper::Default ();
  P5wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
  //mac-layer for Platoon5
  NqosWifiMacHelper P5mac = NqosWifiMacHelper::Default ();
  P5mac.SetType ("ns3::AdhocWifiMac");

  

 

    //phy-layer for Company network
  YansWifiChannelHelper CMchannel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper CMphy = YansWifiPhyHelper::Default ();
  CMphy.SetChannel (CMchannel.Create ());
  
  WifiHelper CMwifi = WifiHelper::Default ();
  CMwifi.SetRemoteStationManager ("ns3::AarfWifiManager");
  //mac-layer for Company network
  NqosWifiMacHelper CMmac = NqosWifiMacHelper::Default ();
  CMmac.SetType ("ns3::AdhocWifiMac");
  
  //interfaces for Platoon1,2,3,4,5 AND Company
  //NetDevices
  NetDeviceContainer P1Devices, P2Devices, P3Devices, P4Devices, P5Devices, CMDevices;
  P1Devices = P1wifi.Install (P1phy, P1mac, Platoon1);
  P2Devices = P2wifi.Install (P2phy, P2mac, Platoon2);
  P3Devices = P3wifi.Install (P3phy, P3mac, Platoon3);
  P4Devices = P4wifi.Install (P4phy, P4mac, Platoon4);
  P5Devices = P5wifi.Install (P5phy, P5mac, Platoon5);
  
  //We got CMNodes from Platoon Nodes Containers
  //Assigning CMDvices to CMNodes makes each CMNode have 2 interfaces
  CMDevices = CMwifi.Install (CMphy, CMmac, Company);
  
  //mobility
  MobilityHelper mobility1, mobility2, mobility3, mobility4, mobility5;

  mobility1.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                 "X", StringValue ("100.0"),
                                 "Y", StringValue ("100.0"),
                                 "Rho", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                 "Theta", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=6.28]")); //2*pi = 6.28
  mobility1.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 1000, 0, 1000)));
                             
  mobility2.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                 "X", StringValue ("500.0"),
                                 "Y", StringValue ("100.0"),
                                 "Rho", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                 "Theta", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=6.28]")); //2*pi = 6.28
  mobility2.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 1000, 0, 1000)));
                             
  mobility3.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                 "X", StringValue ("900.0"),
                                 "Y", StringValue ("100.0"),
                                 "Rho", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                 "Theta", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=6.28]")); //2*pi = 6.28
  mobility3.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 1000, 0, 1000)));
                             
  mobility4.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                 "X", StringValue ("200.0"),
                                 "Y", StringValue ("900.0"),
                                 "Rho", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                 "Theta", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=6.28]")); //2*pi = 6.28
  mobility4.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 1000, 0, 1000)));
                             
  mobility5.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                 "X", StringValue ("800.0"),
                                 "Y", StringValue ("900.0"),
                                 "Rho", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                 "Theta", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=6.28]")); //2*pi = 6.28
  mobility5.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 1000, 0, 1000)));
  

  mobility1.Install (Platoon1);
  mobility2.Install (Platoon2);
  mobility3.Install (Platoon3);
  mobility4.Install (Platoon4);
  mobility5.Install (Platoon5);
  //We got CMNodes from Platoon Nodes Containers
  //No need to assign mobility to CMNodes again.

  //OLSR routing protocal for Platoon
  OlsrHelper olsr;
  //DSDV routing protocal for CMNodes
  IdrmHelper dsdv;

  //Routing list
  Ipv4ListRoutingHelper PList, CMList;
  PList.Add (olsr, 0);
  //gateway has 2 routing protocals
  CMList.Add (olsr, 1);
  CMList.Add (dsdv, 0);//second parameter is priority

  InternetStackHelper PStack;
  InternetStackHelper CMStack;
  PStack.SetRoutingHelper (PList);
  CMStack.SetRoutingHelper (CMList);

  PStack.Install (Platoon1.Get(4));
  PStack.Install (Platoon1.Get(5));
  PStack.Install (Platoon1.Get(6));

  
  PStack.Install (Platoon2.Get(4));
  PStack.Install (Platoon2.Get(5));
  PStack.Install (Platoon2.Get(6));

  
  PStack.Install (Platoon3.Get(4));
  PStack.Install (Platoon3.Get(5));
  PStack.Install (Platoon3.Get(6));
  

  PStack.Install (Platoon4.Get(4));
  PStack.Install (Platoon4.Get(5));
  PStack.Install (Platoon4.Get(6));
  

  PStack.Install (Platoon5.Get(4));
  PStack.Install (Platoon5.Get(5));
  PStack.Install (Platoon5.Get(6));
          

  CMStack.Install (Company);


  Ipv4AddressHelper P1Address;
  Ipv4AddressHelper P2Address;
  Ipv4AddressHelper P3Address;
  Ipv4AddressHelper P4Address;
  Ipv4AddressHelper P5Address;
  Ipv4AddressHelper CMAddress;

  P1Address.SetBase ("192.168.2.0", "255.255.255.0");
  P2Address.SetBase ("192.168.3.0", "255.255.255.0");
  P3Address.SetBase ("192.168.4.0", "255.255.255.0");
  P4Address.SetBase ("192.168.5.0", "255.255.255.0");
  P5Address.SetBase ("192.168.6.0", "255.255.255.0");
  CMAddress.SetBase ("192.168.7.0", "255.255.255.0");

  Ipv4InterfaceContainer P1Interfaces;
  Ipv4InterfaceContainer P2Interfaces;
  Ipv4InterfaceContainer P3Interfaces;
  Ipv4InterfaceContainer P4Interfaces;
  Ipv4InterfaceContainer P5Interfaces;
  Ipv4InterfaceContainer CMInterfaces;

  P1Interfaces = P1Address.Assign (P1Devices);
  P2Interfaces = P2Address.Assign (P2Devices);
  P3Interfaces = P3Address.Assign (P3Devices);
  P4Interfaces = P4Address.Assign (P4Devices);
  P5Interfaces = P5Address.Assign (P5Devices);
  CMInterfaces = CMAddress.Assign (CMDevices);


  //run simulation
  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (Platoon1.Get (6));//send from an ordinary node from Platoon1
  serverApps.Start (Seconds (29.0));
  serverApps.Stop (Seconds (300.0));

  UdpEchoClientHelper echoClient (P1Interfaces.GetAddress (6), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1000));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (Platoon5.Get (6));//receive by an ordinary node from Platoon5
  clientApps.Start (Seconds (30.0));
  clientApps.Stop (Seconds (300.0));

  //AnimationInterface anim ("animation.xml");
  //anim.SetMobilityPollInterval (Seconds (1));
  //anim.EnablePacketMetadata (true);

  Simulator::Stop (Seconds (300.0));

  P1phy.EnablePcap("Platoon1",P1Devices);
  P5phy.EnablePcap("Platoon5",P5Devices);
  CMphy.EnablePcap("Company",CMDevices);
  

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;

}//main
