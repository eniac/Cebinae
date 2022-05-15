#ifndef MY_SOURCE_ID_TAG_H
#define MY_SOURCE_ID_TAG_H

#include "ns3/tag.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include <iostream>

namespace ns3 {

class MySourceIDTag : public Tag
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (TagBuffer i) const;
  virtual void Deserialize (TagBuffer i);
  virtual void Print (std::ostream &os) const;

  void Set (uint32_t value);

  uint32_t Get (void) const;
private:
  uint32_t m_MySourceIDValue;
};

}
#endif