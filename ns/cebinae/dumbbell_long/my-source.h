#ifndef MY_SOURCE_H
#define MY_SOURCE_H

#include "ns3/address.h"
#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/internet-module.h"
#include "ns3/data-rate.h"
#include "ns3/traced-callback.h"
#include "ns3/seq-ts-size-header.h"

using namespace ns3;

class MySource : public Application 
{
public:

  MySource ();
  virtual ~MySource();

  // Default OnOffApp creates socket until app start time, can't access and configure the tracing externally
  void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, DataRate dataRate, uint32_t appid, bool poisson);

  uint32_t GetPacketsSent();

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void ScheduleTx (void);
  void SendPacket (void);

  Ptr<Socket>     m_socket;
  Address         m_peer;
  uint32_t        m_packetSize;
  DataRate        m_dataRate;
  EventId         m_sendEvent;
  bool            m_running;
  uint32_t        m_packetsSent;

  uint32_t        m_sourceid;

  Ptr<ExponentialRandomVariable> m_var;
};

MySource::MySource ()
  : m_socket (0), 
    m_peer (), 
    m_packetSize (0), 
    m_dataRate (0), 
    m_sendEvent (), 
    m_running (false), 
    m_packetsSent (0)
{
}

MySource::~MySource()
{
  m_socket = 0;
}

void
MySource::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, DataRate dataRate, uint32_t sourceid, bool poisson)
{
  m_socket = socket;
  m_peer = address;
  m_packetSize = packetSize;
  m_dataRate = dataRate;
  m_sourceid = sourceid;

  m_var = CreateObject<ExponentialRandomVariable> ();
  // No need for poisson as the demand is infinite anyway and the packet gap pattern is determined by the underlying transport
}

void
MySource::StartApplication (void)
{
  m_running = true;
  m_packetsSent = 0;
  m_socket->Bind ();
  m_socket->Connect (m_peer);
  SendPacket ();
}

void 
MySource::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

void 
MySource::SendPacket (void)
{
  Ptr<Packet> packet = Create<Packet> (m_packetSize);

  MySourceIDTag tag;
  tag.Set (m_sourceid);
  // PacketTag can be pulled out at intermediate NetDevice but not the destination sink app
  // packet->AddPacketTag (tag);
  packet->AddByteTag (tag);  // For persistence

  m_socket->Send (packet);

  // Infinite demand
  // if (++m_packetsSent < m_nPackets)
  ++m_packetsSent;
  ScheduleTx ();
}

void 
MySource::ScheduleTx (void)
{
  if (m_running)
    {
      Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
      m_sendEvent = Simulator::Schedule (tNext, &MySource::SendPacket, this);
    }
}

uint32_t MySource::GetPacketsSent (void) {
  return m_packetsSent;
}

#endif