
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
#include "ns3/dsr-module.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("startopology");

int main(int argc, char* argv[])
{
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  //LogComponentEnable ("AodvRoutingProtocol", LOG_LEVEL_LOGIC);

  NodeContainer GNodes;
  NodeContainer LNodes;
  NodeContainer RNodes;
  NodeContainer UNodes;
  
  int lg=2;//gateway num in left subnet
  int rg=2;//gateway num in right subnet
  int ug=2;//gateway num in up subnet
  int ln=3;//common node num in left subnet
  int rn=3;//common node num in right subnet
  int un=3;//common node num in up subnet
  
  GNodes.Create(lg+rg+ug);
  LNodes.Create(ln);
  for(int i=0;i<lg+rg+ug;i++)
  {
  	LNodes.Add(GNodes.Get(i));
  	RNodes.Add(GNodes.Get(i));
  }
  RNodes.Create(rn);
  UNodes.Create(un);
  for(int i=0;i<lg+rg+ug;i++)
  {
  	UNodes.Add(GNodes.Get(i));
  }
  
  //set node type: 0 = normal node; 1 = gateway node; 2 = gateway candidate
  for(int i=0;i<ln;i++)
  {
  	LNodes.Get(i)->SetNType(0);
  }
  for(int i=lg+rg+ug;i<lg+rg+ug+rn;i++)
  {
  	RNodes.Get(i)->SetNType(0);
  }
  for(int i=0;i<un;i++)
  {
  	UNodes.Get(i)->SetNType(0);
  }
  for(int i=0;i<(lg+rg+ug)/2;i++)
  {
  	GNodes.Get(i)->SetNType(2);
  }
  for(int i=(lg+rg+ug)/2;i<lg+rg+ug;i++)
  {
  	GNodes.Get(i)->SetNType(1);
  }

  YansWifiChannelHelper Lchannel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper Lphy = YansWifiPhyHelper::Default ();
  Lphy.SetChannel (Lchannel.Create ());

  WifiHelper Lwifi = WifiHelper::Default ();
  Lwifi.SetRemoteStationManager ("ns3::AarfWifiManager");

  NqosWifiMacHelper Lmac = NqosWifiMacHelper::Default ();

  Lmac.SetType ("ns3::AdhocWifiMac");

  YansWifiChannelHelper Rchannel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper Rphy = YansWifiPhyHelper::Default ();
  Rphy.SetChannel (Rchannel.Create ());

  WifiHelper Rwifi = WifiHelper::Default ();
  Rwifi.SetRemoteStationManager ("ns3::AarfWifiManager");

  NqosWifiMacHelper Rmac = NqosWifiMacHelper::Default ();

  Rmac.SetType ("ns3::AdhocWifiMac");
  
  YansWifiChannelHelper Uchannel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper Uphy = YansWifiPhyHelper::Default ();
  Uphy.SetChannel (Uchannel.Create ());

  WifiHelper Uwifi = WifiHelper::Default ();
  Uwifi.SetRemoteStationManager ("ns3::AarfWifiManager");

  NqosWifiMacHelper Umac = NqosWifiMacHelper::Default ();

  Umac.SetType ("ns3::AdhocWifiMac");

  NetDeviceContainer LDevices;
  NetDeviceContainer RDevices;
  NetDeviceContainer UDevices;
  LDevices = Lwifi.Install (Lphy, Lmac, LNodes);
  RDevices = Rwifi.Install (Rphy, Rmac, RNodes);
  UDevices = Uwifi.Install (Uphy, Umac, UNodes);
    

  MobilityHelper Lmobility;
  MobilityHelper Rmobility;
  MobilityHelper Umobility;

  Lmobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (60.0),
                                 "DeltaX", DoubleValue (3.0),
                                 "DeltaY", DoubleValue (3.0),
                                 "GridWidth", UintegerValue (3),
                                 "LayoutType", StringValue ("RowFirst"));

  Lmobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 100, 0, 100)));

  Rmobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (60.0),
                                 "MinY", DoubleValue (60.0),
                                 "DeltaX", DoubleValue (3.0),
                                 "DeltaY", DoubleValue (3.0),
                                 "GridWidth", UintegerValue (3),
                                 "LayoutType", StringValue ("RowFirst"));

  Rmobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 100, 0, 100)));
  
  Umobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (30.0),
                                 "MinY", DoubleValue (30.0),
                                 "DeltaX", DoubleValue (3.0),
                                 "DeltaY", DoubleValue (3.0),
                                 "GridWidth", UintegerValue (3),
                                 "LayoutType", StringValue ("RowFirst"));

  Umobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 100, 0, 100)));

  NodeContainer LG;
  NodeContainer RG;
  NodeContainer UG;
  for(int i=0;i<ln;i++)
  {
  	LG.Add(LNodes.Get(i));
  }
  for(int i=0;i<lg;i++)
  {
  	LG.Add(GNodes.Get(i));
  }
  for(int i=0;i<un;i++)
  {
  	UG.Add(UNodes.Get(i));
  }
  for(int i=lg;i<lg+ug;i++)
  {
  	UG.Add(GNodes.Get(i));
  }
  for(int i=lg+rg+ug;i<rn+lg+rg+ug;i++)
  {
  	RG.Add(RNodes.Get(i));
  }
  for(int i=lg+ug;i<lg+ug+rg;i++)
  {
  	RG.Add(GNodes.Get(i));
  }
  
  Lmobility.Install (LG);
  Rmobility.Install (RG);
  Umobility.Install (UG);

  // Enable OLSR
  OlsrHelper Lolsr;
  OlsrHelper Golsr;
  OlsrHelper Rolsr;
  OlsrHelper Uolsr;
  // Enable AODV
  AodvHelper Laodv;
  AodvHelper Gaodv;
  AodvHelper Raodv;
  AodvHelper Uaodv;

  Ipv4ListRoutingHelper Llist;
  //Llist.Add (Laodv, 0);
  Llist.Add (Lolsr, 0);
  Ipv4ListRoutingHelper Glist;
  //Glist.Add (Gaodv, 0);
  Glist.Add (Golsr, 10);
  //Glist.Add (Gaodv, 10);
  Ipv4ListRoutingHelper Rlist;
  Rlist.Add (Rolsr, 0);
  //Rlist.Add (Raodv, 0);
  Ipv4ListRoutingHelper Ulist;
  Ulist.Add (Uolsr, 0);
  //Ulist.Add (Uaodv, 0);

  InternetStackHelper Lstack;
  InternetStackHelper Gstack;
  InternetStackHelper Rstack;
  InternetStackHelper Ustack;
  Lstack.SetRoutingHelper (Llist);
  Gstack.SetRoutingHelper (Glist);
  Rstack.SetRoutingHelper (Rlist);
  Ustack.SetRoutingHelper (Ulist);
  for(int i=0;i<ln;i++)
  {
  	Lstack.Install (LNodes.Get(i));
  }
  for(int i=0;i<un;i++)
  {
  	Ustack.Install (UNodes.Get(i));
  }
  Gstack.Install (GNodes);
  for(int i=lg+rg+ug;i<lg+rg+ug+rn;i++)
  {
  	Rstack.Install (RNodes.Get(i));
  }

  //Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper>  ("testRoutingTable",std::ios::out);
  //Laodv.PrintRoutingTableAllEvery(Seconds(10), routingStream);

  Ipv4AddressHelper Laddress;
  Ipv4AddressHelper Raddress;
  Ipv4AddressHelper Uaddress;
  Laddress.SetBase ("10.1.1.0", "255.255.255.0");
  Raddress.SetBase ("10.1.2.0", "255.255.255.0");
  Uaddress.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer LInterfaces;
  Ipv4InterfaceContainer RInterfaces;
  Ipv4InterfaceContainer UInterfaces;
  LInterfaces = Laddress.Assign (LDevices);
  RInterfaces = Raddress.Assign (RDevices);
  UInterfaces = Uaddress.Assign (UDevices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (RNodes.Get (lg+rg+ug+rn-1));
  serverApps.Start (Seconds (0.0));
  serverApps.Stop (Seconds (100.0));

  UdpEchoClientHelper echoClient (RInterfaces.GetAddress (lg+rg+ug+rn-1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.01)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = 
    echoClient.Install (LNodes.Get (0));
  clientApps.Start (Seconds (5.0));
  clientApps.Stop (Seconds (100.0));

  //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  
  AnimationInterface anim ("animation.xml");
  anim.SetMobilityPollInterval (Seconds (1));
  //anim.SetConstantPosition (wifiNodesL.Get(1), 0, 0);
  //anim.SetConstantPosition (wifiNodesL.Get(0), 100, 0);
  //anim.SetConstantPosition (wifiNodesR.Get(1), 200, 0);
  //anim.EnablePacketMetadata (true);

  Simulator::Stop (Seconds (100.0));

  Lphy.EnablePcap ("starL", LDevices);
  Rphy.EnablePcap ("starR", RDevices);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
