/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 Tom Henderson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Tom Henderson <tomh@tomh.org>
 */

// This example shows (and tests) some possible configurations for
// the Wi-Fi physical layer, particularly the interaction between
// WifiHelper.SetStandard () and the physical layer channel number,
// center frequency, and channel width.

#include "ns3/log.h"
#include "ns3/command-line.h"
#include "ns3/config-store.h"
#include "ns3/config.h"
#include "ns3/boolean.h"
#include "ns3/uinteger.h"
#include "ns3/string.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-phy.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/wifi-net-device.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("WifiPhyConfigurationExample");

Ptr<YansWifiPhy>
GetYansWifiPhyPtr (const NetDeviceContainer &nc)
{
  Ptr<WifiNetDevice> wnd = nc.Get (0)->GetObject<WifiNetDevice> ();
  Ptr<WifiPhy> wp = wnd->GetPhy ();
  return wp->GetObject<YansWifiPhy> ();
}

void
PrintAttributesIfEnabled (bool enabled)
{
  if (enabled)
    {
      ConfigStore outputConfig;
      outputConfig.ConfigureAttributes ();
    }
}

int main (int argc, char *argv[])
{
  uint32_t testCase = 0;
  bool printAttributes = false;
  bool exceptionThrown = false;

  CommandLine cmd (__FILE__);
  cmd.AddValue ("testCase", "Test case", testCase);
  cmd.AddValue ("printAttributes", "If true, print out attributes", printAttributes);
  cmd.Parse (argc, argv);

  NodeContainer wifiStaNode;
  wifiStaNode.Create (1);
  NodeContainer wifiApNode;
  wifiApNode.Create (1);

  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phy;
  phy.SetChannel (channel.Create ());
  WifiHelper wifi;
  wifi.SetRemoteStationManager ("ns3::IdealWifiManager");

  // Configure and declare other generic components of this example
  Ssid ssid;
  ssid = Ssid ("wifi-phy-configuration");
  WifiMacHelper macSta;
  macSta.SetType ("ns3::StaWifiMac",
                  "Ssid", SsidValue (ssid),
                  "ActiveProbing", BooleanValue (false));
  WifiMacHelper macAp;
  macAp.SetType ("ns3::ApWifiMac",
                 "Ssid", SsidValue (ssid),
                 "BeaconInterval", TimeValue (MicroSeconds (102400)),
                 "BeaconGeneration", BooleanValue (true));
  NetDeviceContainer staDevice;
  NetDeviceContainer apDevice;
  Ptr<YansWifiPhy> phySta;
  Config::SetDefault ("ns3::ConfigStore::Filename", StringValue ("output-attributes-" + std::to_string (testCase) + ".txt"));
  Config::SetDefault ("ns3::ConfigStore::FileFormat", StringValue ("RawText"));
  Config::SetDefault ("ns3::ConfigStore::Mode", StringValue ("Save"));

  switch (testCase)
    {
    case 0:
      // Default configuration, without WifiHelper::SetStandard or WifiHelper
      phySta = CreateObject<YansWifiPhy> ();
      // The default results in an invalid configuration
      NS_ASSERT (!phySta->GetOperatingChannel ().IsSet ());
      PrintAttributesIfEnabled (printAttributes);
      break;

    // The following cases test the setting of WifiPhyStandard alone;
    // i.e. without further channel number/width/frequency configuration

    case 1:
      // By default, WifiHelper will use WIFI_STANDARD_80211a
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 36, width 20, frequency 5180
      NS_ASSERT (phySta->GetChannelNumber () == 36);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5180);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 2:
      wifi.SetStandard (WIFI_STANDARD_80211b);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 1, width 22, frequency 2412
      NS_ASSERT (phySta->GetChannelNumber () == 1);
      NS_ASSERT (phySta->GetChannelWidth () == 22);
      NS_ASSERT (phySta->GetFrequency () == 2412);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 3:
      wifi.SetStandard (WIFI_STANDARD_80211g);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 1, width 20, frequency 2412
      NS_ASSERT (phySta->GetChannelNumber () == 1);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 2412);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 4:
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 36, width 20, frequency 5180
      NS_ASSERT (phySta->GetChannelNumber () == 36);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5180);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 5:
      wifi.SetStandard (WIFI_STANDARD_80211n_2_4GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 1, width 20, frequency 2412
      NS_ASSERT (phySta->GetChannelNumber () == 1);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 2412);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 6:
      wifi.SetStandard (WIFI_STANDARD_80211ac);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 42, width 80, frequency 5210
      NS_ASSERT (phySta->GetChannelNumber () == 42);
      NS_ASSERT (phySta->GetChannelWidth () == 80);
      NS_ASSERT (phySta->GetFrequency () == 5210);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 7:
      wifi.SetStandard (WIFI_STANDARD_80211ax_2_4GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 1, width 20, frequency 2412
      NS_ASSERT (phySta->GetChannelNumber () == 1);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 2412);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 8:
      wifi.SetStandard (WIFI_STANDARD_80211ax_5GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 42, width 80, frequency 5210
      NS_ASSERT (phySta->GetChannelNumber () == 42);
      NS_ASSERT (phySta->GetChannelWidth () == 80);
      NS_ASSERT (phySta->GetFrequency () == 5210);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 9:
      wifi.SetStandard (WIFI_STANDARD_80211ax_6GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 7, width 80, frequency 5975
      NS_ASSERT (phySta->GetChannelNumber () == 7);
      NS_ASSERT (phySta->GetChannelWidth () == 80);
      NS_ASSERT (phySta->GetFrequency () == 5975);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 10:
      wifi.SetStandard (WIFI_STANDARD_80211p);
      phy.Set ("ChannelWidth", UintegerValue (10));
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 172, width 10, frequency 5860
      NS_ASSERT (phySta->GetChannelNumber () == 172);
      NS_ASSERT (phySta->GetChannelWidth () == 10);
      NS_ASSERT (phySta->GetFrequency () == 5860);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 11:
      wifi.SetStandard (WIFI_STANDARD_80211p);
      phy.Set ("ChannelWidth", UintegerValue (5));
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 171, width 5, frequency 5860
      NS_ASSERT (phySta->GetChannelNumber () == 171);
      NS_ASSERT (phySta->GetChannelWidth () == 5);
      NS_ASSERT (phySta->GetFrequency () == 5860);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 12:
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      phy.Set ("ChannelNumber", UintegerValue (44));
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel 44, width 20, frequency 5220
      NS_ASSERT (phySta->GetChannelNumber () == 44);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5220);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 13:
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      phy.Set ("ChannelNumber", UintegerValue (44));
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // Post-install reconfiguration to channel number 40
      Config::Set ("/NodeList/0/DeviceList/*/$ns3::WifiNetDevice/Phy/$ns3::YansWifiPhy/ChannelNumber", UintegerValue (40));
      Config::Set ("/NodeList/1/DeviceList/*/$ns3::WifiNetDevice/Phy/$ns3::YansWifiPhy/ChannelNumber", UintegerValue (40));
      // We expect channel 40, width 20, frequency 5200
      NS_ASSERT (phySta->GetChannelNumber () == 40);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5200);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 14:
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      phy.Set ("ChannelNumber", UintegerValue (44));
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // Post-install reconfiguration to a 40 MHz channel
      Config::Set ("/NodeList/0/DeviceList/*/$ns3::WifiNetDevice/Phy/$ns3::YansWifiPhy/ChannelNumber", UintegerValue (46));
      Config::Set ("/NodeList/1/DeviceList/*/$ns3::WifiNetDevice/Phy/$ns3::YansWifiPhy/ChannelNumber", UintegerValue (46));
      NS_ASSERT (phySta->GetChannelNumber () == 46);
      NS_ASSERT (phySta->GetChannelWidth () == 40);
      NS_ASSERT (phySta->GetFrequency () == 5230);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 15:
      Config::SetDefault ("ns3::WifiPhy::ChannelNumber", UintegerValue (44));
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // Post-install reconfiguration to a 40 MHz channel
      Config::Set ("/NodeList/0/DeviceList/*/$ns3::WifiNetDevice/Phy/$ns3::YansWifiPhy/ChannelNumber", UintegerValue (46));
      Config::Set ("/NodeList/1/DeviceList/*/$ns3::WifiNetDevice/Phy/$ns3::YansWifiPhy/ChannelNumber", UintegerValue (46));
      NS_ASSERT (phySta->GetChannelNumber () == 46);
      NS_ASSERT (phySta->GetChannelWidth () == 40);
      NS_ASSERT (phySta->GetFrequency () == 5230);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 16:
      // Test that setting Frequency to a non-standard value will throw an exception
      Config::SetDefault ("ns3::WifiPhy::Frequency", UintegerValue (5281));
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      exceptionThrown = false;
      try
        {
          staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
        }
      catch (const std::runtime_error&)
        {
          exceptionThrown = true;
        }
      NS_ASSERT (exceptionThrown);
      exceptionThrown = false;
      try
        {
          apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
        }
      catch (const std::runtime_error&)
        {
          exceptionThrown = true;
        }
      NS_ASSERT (exceptionThrown);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 17:
      // Test that setting Frequency to a standard value will set the
      // channel number correctly
      Config::SetDefault ("ns3::WifiPhy::Frequency", UintegerValue (5500));
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      // We expect channel number to be 100 due to frequency 5500
      NS_ASSERT (phySta->GetChannelNumber () == 100);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5500);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 18:
      // Set a wrong channel after initialization
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      exceptionThrown = false;
      try
        {
          phySta->SetOperatingChannel (99, 5185, 40);
        }
      catch (const std::runtime_error&)
        {
          exceptionThrown = true;
        }
      NS_ASSERT (exceptionThrown);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 19:
      // Test how channel number behaves when frequency is non-standard
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      exceptionThrown = false;
      try
        {
          phySta->SetAttribute ("Frequency", UintegerValue (5181));
        }
      catch (const std::runtime_error&)
        {
          exceptionThrown = true;
        }
      // We expect that an exception is thrown due to unknown center frequency 5181
      NS_ASSERT (exceptionThrown);
      phySta->SetAttribute ("Frequency", UintegerValue (5180));
      // We expect channel number to be 36 due to known center frequency 5180
      NS_ASSERT (phySta->GetChannelNumber () == 36);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5180);
      exceptionThrown = false;
      try
        {
          phySta->SetAttribute ("Frequency", UintegerValue (5179));
        }
      catch (const std::runtime_error&)
        {
          exceptionThrown = true;
        }
      // We expect that an exception is thrown due to unknown center frequency 5179
      NS_ASSERT (exceptionThrown);
      phySta->SetAttribute ("ChannelNumber", UintegerValue (36));
      NS_ASSERT (phySta->GetChannelNumber () == 36);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5180);
      PrintAttributesIfEnabled (printAttributes);
      break;
    case 20:
      // Set both channel and frequency to consistent values before initialization
      Config::SetDefault ("ns3::WifiPhy::Frequency", UintegerValue (5200));
      Config::SetDefault ("ns3::WifiPhy::ChannelNumber", UintegerValue (40));
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      NS_ASSERT (phySta->GetChannelNumber () == 40);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5200);
      // Set both channel and frequency to consistent values after initialization
      wifi.SetStandard (WIFI_STANDARD_80211n_5GHZ);
      staDevice = wifi.Install (phy, macSta, wifiStaNode.Get (0));
      apDevice = wifi.Install (phy, macAp, wifiApNode.Get (0));
      phySta = GetYansWifiPhyPtr (staDevice);
      phySta->SetAttribute ("Frequency", UintegerValue (5200));
      phySta->SetAttribute ("ChannelNumber", UintegerValue (40));
      NS_ASSERT (phySta->GetChannelNumber () == 40);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5200);
      // Set both channel and frequency to inconsistent values
      phySta->SetAttribute ("Frequency", UintegerValue (5200));
      phySta->SetAttribute ("ChannelNumber", UintegerValue (36));
      // We expect channel number to be 36
      NS_ASSERT (phySta->GetChannelNumber () == 36);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5180);
      phySta->SetAttribute ("ChannelNumber", UintegerValue (36));
      phySta->SetAttribute ("Frequency", UintegerValue (5200));
      // We expect channel number to be 40
      NS_ASSERT (phySta->GetChannelNumber () == 40);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5200);
      exceptionThrown = false;
      try
        {
          phySta->SetAttribute ("Frequency", UintegerValue (5179));
        }
      catch (const std::runtime_error&)
        {
          exceptionThrown = true;
        }
      phySta->SetAttribute ("ChannelNumber", UintegerValue (36));
      // We expect channel number to be 36 and an exception to be thrown
      NS_ASSERT (phySta->GetChannelNumber () == 36);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5180);
      NS_ASSERT (exceptionThrown);
      phySta->SetAttribute ("ChannelNumber", UintegerValue (36));
      exceptionThrown = false;
      try
        {
          phySta->SetAttribute ("Frequency", UintegerValue (5179));
        }
      catch (const std::runtime_error&)
        {
          exceptionThrown = true;
        }
      // We expect channel number to be 36 and an exception to be thrown
      NS_ASSERT (phySta->GetChannelNumber () == 36);
      NS_ASSERT (phySta->GetChannelWidth () == 20);
      NS_ASSERT (phySta->GetFrequency () == 5180);
      NS_ASSERT (exceptionThrown);
      PrintAttributesIfEnabled (printAttributes);
      break;
    default:
      std::cerr << "Invalid testcase number " << testCase << std::endl;
      exit (1);
      break;
    }

  // No need to Simulator::Run (); this is a configuration example
  Simulator::Destroy ();
}
