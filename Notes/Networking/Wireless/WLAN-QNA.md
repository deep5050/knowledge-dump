**What is WLAN and how does it differ from LAN?**

**WLAN (Wireless Local Area Network)** uses radio waves to connect devices within a limited area, while **LAN (Local Area Network)** uses physical cables.

**Key Differences:**
- **Connection Medium**: WLAN uses radio frequencies; LAN uses Ethernet cables
- **Mobility**: WLAN allows device movement within coverage area; LAN requires fixed connections
- **Installation**: WLAN is easier to deploy, no cable infrastructure needed
- **Security**: WLAN requires encryption over airwaves; LAN has inherent physical security
- **Performance**: LAN typically offers higher, more consistent speeds
- **Cost**: WLAN has lower installation costs but higher equipment costs per connection
- **Interference**: WLAN susceptible to radio interference; LAN immune to wireless interference

---

**Explain the IEEE 802.11 standards and their differences (a/b/g/n/ac/ax)**

**802.11b (1999):**
- Frequency: 2.4 GHz
- Max Speed: 11 Mbps
- Range: Good indoor penetration

**802.11a (1999):**
- Frequency: 5 GHz
- Max Speed: 54 Mbps
- Range: Shorter than b, less interference

**802.11g (2003):**
- Frequency: 2.4 GHz
- Max Speed: 54 Mbps
- Backward compatible with 802.11b

**802.11n (2009):**
- Frequency: 2.4 GHz and 5 GHz (dual-band)
- Max Speed: 600 Mbps
- Features: MIMO technology, channel bonding

**802.11ac (2013):**
- Frequency: 5 GHz only
- Max Speed: Up to 6.93 Gbps
- Features: Multi-user MIMO, wider channels (80/160 MHz)

**802.11ax/Wi-Fi 6 (2019):**
- Frequency: 2.4 GHz, 5 GHz, and 6 GHz
- Max Speed: Up to 9.6 Gbps
- Features: OFDMA, improved efficiency, better performance in dense environments

---

**What frequency bands does Wi-Fi operate on?**

**2.4 GHz Band:**
- Channels: 1-14 (only 1, 6, 11 non-overlapping in North America)
- Range: Longer range, better wall penetration
- Speed: Lower data rates
- Interference: More crowded, shared with Bluetooth, microwaves

**5 GHz Band:**
- Channels: Many more non-overlapping channels available
- Range: Shorter range, less wall penetration
- Speed: Higher data rates
- Interference: Less congested

**6 GHz Band (Wi-Fi 6E/7):**
- Newest band with extensive spectrum availability
- Very wide channels possible (up to 320 MHz)
- Currently less device support but growing
- Requires newer, compatible hardware

---

**What is the difference between infrastructure and ad-hoc mode?**

**Infrastructure Mode:**
- Uses a central Access Point (AP) as a hub
- All communication goes through the AP
- Devices connect to the AP, not directly to each other
- Provides connection to wired network resources
- More secure and manageable
- Standard mode for enterprise and home networks
- Supports services like DHCP, internet access

**Ad-hoc Mode (IBSS - Independent Basic Service Set):**
- Direct device-to-device communication without an AP
- Forms a peer-to-peer wireless network
- Also called "computer-to-computer" or "peer-to-peer" mode
- No central management or internet access (unless one device shares)
- Less secure and harder to manage
- Useful for temporary file sharing or gaming
- Limited range and scalability

**Key Difference:** Infrastructure mode is centralized through an AP, while ad-hoc mode is decentralized with direct device communication.


**What is an Access Point and what does it do?**

An Access Point (AP) is a networking device that acts as a bridge between wireless devices and a wired network. It creates a wireless coverage area where devices can connect to the network.

**Primary functions:**
- Converts wired network signals to wireless radio signals and vice versa
- Manages wireless client authentication and association
- Forwards data between wireless clients and the wired network
- Broadcasts the network name (SSID) for clients to discover
- Handles encryption/decryption of wireless traffic
- Manages multiple clients simultaneously within its coverage area

---

**Explain the role of a Wireless LAN Controller**

A Wireless LAN Controller (WLC) is a centralized management device that controls and coordinates multiple access points in an enterprise wireless network.

**Key roles:**
- **Centralized Management**: Configure and monitor all APs from a single interface
- **Security Enforcement**: Apply consistent security policies across all APs
- **Traffic Management**: Handle client authentication, load balancing, and traffic shaping
- **Roaming Management**: Enable seamless handoffs as clients move between APs
- **Firmware Updates**: Push updates and configurations to all managed APs
- **Radio Resource Management**: Optimize channel assignments and power levels automatically

---

**What is the difference between a lightweight AP and autonomous AP?**

**Lightweight AP:**
- Requires a WLC to function - cannot operate independently
- Most intelligence and processing handled by the controller
- Configuration and management done centrally through WLC
- Lower cost per unit but requires controller investment
- Easier to manage at scale
- Uses protocols like CAPWAP to communicate with controller

**Autonomous AP:**
- Functions independently without requiring a controller
- All intelligence and configuration stored locally on the AP
- Each AP managed individually through its own interface
- Higher per-unit cost but no controller needed
- More complex to manage multiple units
- Suitable for small deployments or standalone applications

---

**What factors affect wireless signal strength and coverage?**

**Physical Factors:**
- **Distance**: Signal strength decreases with distance from AP
- **Obstacles**: Walls, floors, furniture, and metal objects cause signal attenuation
- **Building Materials**: Concrete, metal, and thick walls block signals more than drywall
- **Antenna Type**: Omnidirectional vs directional antennas affect coverage patterns

**Environmental Factors:**
- **Interference**: Other Wi-Fi networks, microwave ovens, Bluetooth devices
- **Weather**: Rain and humidity can affect outdoor wireless links
- **Electromagnetic Interference**: Motors, fluorescent lights, other electronic devices

**Technical Factors:**
- **Frequency Band**: 2.4 GHz travels farther but 5 GHz has less interference
- **Transmit Power**: Higher power increases range but may cause interference
- **Antenna Placement**: Height and positioning significantly impact coverage
- **Channel Selection**: Overlapping channels cause interference and reduce performance



BSSID (Basic Service Set Identifier) 
What it is: The MAC address of the access point.
Purpose: To uniquely identify a specific access point within a wireless network.
How it's used: It's a technical identifier that helps devices differentiate between different APs, even if they broadcast the same SSID.
Example: A unique 12-character MAC address like A1:B2:C3:D4:E5:F6.
Relationship between SSID and BSSID
SSID: The user-facing network name, like "Home_Net". 
BSSID: The unique identifier of the access point, like 00:1A:2B:3C:4D:5E, that is associated with "Home_Net". 
In an environment with multiple access points (like in a large building), each AP has its own unique BSSID but may broadcast the same SSID. This allows a device to connect to the strongest or most appropriate AP for better performance. 
