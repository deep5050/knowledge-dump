# Switch

A network switch is a network device that connects devices within a local area network (LAN) and intelligently forwards data packets between them. It operates at the data link layer (Layer 2) and is a fundamental building block in modern Ethernet networks.

## Key functionalities

1. **Learn:**
- Learning is the process by which a network switch populates its MAC address table with the MAC addresses of devices connected to its ports.
- <mark style="background: #FFF3A3A6;">When a switch receives an Ethernet frame from a device on one of its ports, it reads the source MAC address of the frame and records it in its MAC address table along with the port number from which the frame was received.</mark>
- This learning process allows the switch to associate MAC addresses with specific ports, which is essential for making forwarding decisions later.

2. **Flood:**
- Flooding is a mechanism used by a switch when it receives a frame with an unknown destination MAC address.
- <mark style="background: #FFF3A3A6;">When a switch receives a frame for which it does not have an entry in its MAC address table (unknown unicast or multicast/broadcast), it will flood the frame to all ports, except the port on which the frame was received.</mark>
- This is done to ensure that the frame reaches its destination device, which may be on an unknown or newly connected port.

3. **Forward:**
- Forwarding is the action taken by a switch to <mark style="background: #ADCCFFA6;">transmit an incoming Ethernet frame to the appropriate destination port</mark> based on the destination MAC address recorded in its MAC address table.
- When a switch receives a frame with a known destination MAC address, it refers to its MAC address table to determine the port to which the frame should be forwarded.
- The switch then transmits the frame only to the port associated with the destination MAC address, ensuring efficient and targeted data transmission.

[Everything Switches do - Part 2 - Networking Fundamentals - Lesson 4 - YouTube](https://www.youtube.com/watch?v=G7GyWjJtjNs)
[Network switches explained, all you need to know - YouTube](https://www.youtube.com/watch?v=DWukAUHi4Oc)

## Need for L3 capabilities in a switch (A smart Switch)

The introduction of Layer 3 (L3) capabilities in a switch addresses several needs and requirements in modern networking environments. Here are some of the key reasons why L3 capabilities are essential in switches:

1. **IP Routing:** L3 switches can perform IP routing, allowing them to make forwarding decisions based on IP addresses. This enables them to <mark style="background: #ADCCFFA6;">route traffic between different subnets and VLANs</mark>, making them more versatile and capable of handling more complex network topologies.

2. **Inter-VLAN Routing:** <mark style="background: #BBFABBA6;">L3 switches can route traffic between different VLANs. This eliminates the need for an external router to perform inter-VLAN communication, providing a more efficient and cost-effective solution for networks with multiple VLANs.</mark>

3. **Scalability:** As networks grow and become more complex, the need for efficient IP routing and inter-VLAN communication increases. L3 switches offer the scalability required to handle larger networks with multiple subnets and VLANs.

4. **Reduced Network Latency:** <mark style="background: #FFF3A3A6;">By enabling IP routing within the switch, L3 capabilities help reduce network latency by allowing devices on the same subnet or VLAN to communicate directly without needing to go through an external router.</mark>

5. **Improved Network Performance:** L3 switches can perform packet forwarding at wire speed, allowing for faster data processing and improved network performance.

6. **Convergence of Networks:** In converged networks that carry both data and voice traffic, L3 switches can provide Quality of Service (QoS) features to prioritize voice traffic, ensuring optimal voice call quality.

7. **Security and Access Control:** L3 switches can enforce access control lists (ACLs) and security policies at the IP level, providing enhanced security and traffic filtering capabilities.

8. **Simplified Network Architecture:** By integrating IP routing capabilities within the switch, network administrators can reduce the number of devices in the network, leading to a more streamlined and simplified network architecture.

9. **Cost-Effectiveness:** L3 switches with IP routing capabilities can reduce the need for separate routers in the network, resulting in cost savings on equipment and maintenance.

10. **Flexibility in Network Design:** L3 switches offer flexibility in network design, allowing for the creation of dynamic and scalable networks with efficient traffic routing and reduced broadcast domains.

Overall, the inclusion of Layer 3 capabilities in a switch brings increased flexibility, scalability, and performance, enabling them to handle the growing demands of modern networks with diverse communication requirements and complex traffic patterns.


# Smart Switch

Here are some key characteristics and features of smart network switches:

1. **Management Capabilities:** Smart switches <mark style="background: #BBFABBA6;">can be configured and monitored through a web interface, command-line interface (CLI)</mark>, or a dedicated management software. This allows network administrators to have more control over the switch's behavior and settings.

2. **VLAN Support:** <mark style="background: #BBFABBA6;">Virtual Local Area Networks (VLANs) can be set up on smart switches to segment the network and improve security and performance.</mark>

3. **Quality of Service (QoS):** Smart switches often support QoS features, enabling administrators to<mark style="background: #BBFABBA6;"> prioritize certain types of traffic to ensure critical applications get sufficient bandwidth.</mark>

4. **Port Mirroring:**<mark style="background: #FFF3A3A6;"> This feature allows traffic from one port to be mirrored to another port, which is useful for network analysis and monitoring purposes.</mark>

5. **Link Aggregation (LAG):** Smart switches may support link aggregation, which allows multiple physical ports to be combined into a single logical link, increasing bandwidth and providing redundancy. #question

6. **Spanning Tree Protocol (STP):** STP is used to prevent network loops in Ethernet networks, and smart switches often include this feature to ensure network stability.

7. **Security Features:** Smart switches offer various security features such as<mark style="background: #FFF3A3A6;"> port security, MAC-based authentication, and access control lists (ACLs) to enhance network security.</mark>

8. **Remote Management:** Many smart switches support remote management, enabling administrators to access and configure the switch from off-site locations.

9. **Monitoring and Troubleshooting Tools:** These switches often provide various monitoring tools like port statistics, error logs, and diagnostic utilities to assist with network troubleshooting.

10. **Firmware Upgrades:** <mark style="background: #FFF3A3A6;">Smart switches can have firmware updates, ensuring the switch remains up-to-date with the latest features and security fixes.</mark>

## Typical Ports on a smart switch

Managed or smart network switches typically come with a variety of ports to accommodate different network connectivity needs. Here are the typical ports you can find on such switches:

1. **RJ-45 Ethernet Ports:** These are the standard Ethernet ports that support twisted-pair copper cables and are used for connecting end devices such as computers, printers, servers, and other networking equipment.

2. **SFP (Small Form-Factor Pluggable) Ports:** <mark style="background: #FFF3A3A6;">SFP ports are for fiber-optic connections</mark>, providing high-speed and long-distance data transmission. SFP ports allow you to use different types of SFP modules to adapt to various fiber types and distances.

3. **SFP+ (Small Form-Factor Pluggable Plus) Ports:** These are an upgraded version of SFP ports, offering higher data rates and often used for <mark style="background: #FFF3A3A6;">10 Gigabit Ethernet connections over fiber-optic cables.</mark>

4. **10GBASE-T Ports:** These ports support <mark style="background: #FFF3A3A6;">10 Gigabit Ethernet</mark> over standard twisted-pair copper cables (Cat 6a or Cat 7), allowing for high-speed connections to compatible devices.

5. **Console Port:** A serial console port (usually an RJ-45 port) is provided to access the switch's command-line interface (CLI) for initial setup, configuration, and troubleshooting.

6. **USB Ports:** <mark style="background: #FFF3A3A6;">Some smart switches may have USB ports used for various purposes, such as firmware upgrades or connecting external storage devices.</mark>

7. **Management Port:** Some higher-end smart switches may include a dedicated management port, allowing administrators to connect to a separate management network for enhanced security.

8. **Stacking Ports:** In certain models, you may find special stacking ports that enable multiple switches to be interconnected and operate as a single logical unit, improving scalability and management.

## SFP 

SFP (Small Form-Factor Pluggable) and SFP+ (Small Form-Factor Pluggable Plus) are types of transceiver modules used in networking equipment to provide high-speed data transmission over fiber-optic cables. They are hot-swappable, meaning they can be plugged and unplugged from compatible ports without powering down the networking equipment.

| Feature                   | SFP                                  | SFP+                                  |
|---------------------------|--------------------------------------|--------------------------------------|
| Data Rate                 | Up to 1 Gbps                         | Up to 10 Gbps                        |
| Applications              | 1 Gigabit Ethernet, Fiber Channel   | 10 Gigabit Ethernet                  |
| Backward Compatibility    | Yes (Can work in SFP ports)          | N/A                                  |
| Physical Size             | Same as SFP (Small Form Factor)      | Same as SFP (Small Form Factor)      |
| Fiber Types               | Multimode and Single-mode            | Multimode and Single-mode            |
| Connector Type            | LC Connector                         | LC Connector                         |
| Common Use Cases          | Fast Ethernet connections,          | 10 Gigabit Ethernet connections,     |
|                           | Fiber Channel connections            | Data center deployments              |


<img width="922" height="436" alt="Pasted image 20230719135504" src="https://github.com/user-attachments/assets/2d2c01a9-2397-479f-962a-01c76fb7a4b8" />


## Stacking 

Switch stacking refers to the process of interconnecting multiple network switches to operate as a single logical unit, enhancing performance, management, and scalability. Stacking technology enables network administrators to create a stack of switches that appears and operates as a single switch, simplifying network management and allowing for seamless expansion and high availability. There are typically two main methods of switch stacking: physical stacking and virtual stacking.

**1. Physical Stacking:**
<mark style="background: #FFF3A3A6;">In physical stacking, switches are connected using specialized stacking ports and stacking cables</mark>. These stacking ports are designed specifically for creating the interconnection between switches within the stack. The stacking cables can vary depending on the switch model and manufacturer.
To create a stack, you physically connect the stacking ports of the switches using the appropriate stacking cables. This creates a "daisy <mark style="background: #ADCCFFA6;">chain" or "ring" topology</mark>, where each switch is connected to the next in line, forming a loop or chain of switches.  One of the switches is responsible of all type of operations of the stack and is called the <mark style="background: #FFF3A3A6;">stack master</mark>. The stack master along with other switches in the stack are <mark style="background: #FFF3A3A6;">stack members</mark>. Whenever we want to add a new switch to the stack, the master switch automatically configures it

Key characteristics of physical stacking:
- **Dedicated Stacking Ports:** <mark style="background: #ADCCFFA6;">Stacking ports are distinct from regular Ethernet ports and are used solely for stacking purposes</mark>.
- **Single Logical Unit:** Once the switches are stacked, they act as a single logical switch. They share a single management IP address and configuration, simplifying administration.
- **Enhanced Performance:** Stacked switches work together to provide increased overall switching capacity, aggregate bandwidth, and processing power, leading to improved performance for the network.

**2. Virtual Stacking:**
https://www.cisco.com/c/en/us/products/collateral/switches/catalyst-9000/nb-06-cat-9k-stack-wp-cte-en.html

EXAMPLE: Cisco StackWise Virtual

Virtual stacking, also known as "cluster management" or "logical stacking," is a <mark style="background: #FFF3A3A6;">software-based approach to stacking that does not require specialized stacking ports or cables</mark>. Instead, switches are interconnected using regular Ethernet ports. They communicate with each other through the network, and their configuration and management are handled centrally through software.

Key characteristics of virtual stacking:
- **Regular Ethernet Ports:** Virtual stacking relies on standard Ethernet ports for interconnection, making it more flexible and easier to deploy compared to physical stacking.
- **Single Logical Unit:** Similar to physical stacking, virtual stacking creates a unified logical switch, allowing centralized management and configuration.
- **Simplified Management:** Network administrators can manage and configure all switches in the virtual stack through a single interface.

Both physical and virtual stacking offer benefits in terms of enhanced performance, simplified management, scalability, and high availability. The choice between the two methods depends on the specific needs of the network, the switch models available, and the desired level of flexibility.

Here are the key features and benefits of stacking :

1. **Enhanced Performance:** By stacking switches, you can increase the overall switching capacity and bandwidth of the network. Stacked switches can share data and processing tasks, leading to improved performance and reduced bottlenecks.

2. **Single Logical Unit:** <mark style="background: #FFF3A3A6;">Stacked switches operate as a single logical entity, so they can be managed as if they were a single switch</mark>. This simplifies network management, as administrators don't need to configure each switch individually. They provide us with a <mark style="background: #ADCCFFA6;">shared MAC address table, shared VLAN configuration</mark>, and consolidated management.

3. **Simplified Management:** With stacking, you only need to manage one switch, even if there are multiple physical devices in the stack. This centralized management approach streamlines configuration, monitoring, and troubleshooting tasks.

4. **High Availability:** <mark style="background: #FFF3A3A6;">Stacking provides redundancy and high availability</mark>. If one switch in the stack fails, the remaining switches can continue to function, ensuring minimal downtime and seamless network operation.

5. **Scalability:** Stacking allows for easy expansion of the network by adding more switches to the stack. This makes it convenient to grow the network as demands increase without complex reconfiguration.

6. **Single IP Address:** When switches are stacked, they often share a single IP address, which simplifies network monitoring and management, as <mark style="background: #FFF3A3A6;">you only need to access one IP address to manage the entire stack</mark>.

1. **Interconnect Cables:** To stack switches, you'll need specific stacking cables that connect the stacking ports on each switch. The type of stacking cables required can vary depending on the switch manufacturer and model.

<img width="502" height="259" alt="Pasted image 20230719140152" src="https://github.com/user-attachments/assets/80f24a12-71ea-4feb-a53e-245414d0e11e" />


> in general, the number of switches in a stack can range from a few switches to as many as eight or more, depending on the specific model and technology used. For example, some enterprise-grade switches support stacking sizes of up to 8, 12, or even more switches.



> The aggregate stack bandwidth is a sum of the individual bandwidth capacities of each switch in the stack. For example, if you have four switches in a stack, and each switch has a stacking bandwidth of 40 Gbps, the aggregate stack bandwidth would be 4 switches * 40 Gbps = 160 Gbps.

## Long distance stacking

Long-distance stacking, also known as extended stacking or remote stacking, is a networking technology that allows network switches to be interconnected over long distances to form a single logical stack. It <mark style="background: #FFF3A3A6;">enables network administrators to create a stacked switch configuration even when the switches are physically located in different areas, buildings, or even remote sites.</mark>

Traditional stacking typically requires the switches to be connected using specialized stacking cables, limiting the stack's physical reach to a relatively short distance, often within the same rack or data center. However, long-distance stacking overcomes this limitation by leveraging alternative technologies to extend the stack's reach over greater distances.

The methods used for long-distance stacking can vary based on the switch manufacturer and the specific stacking technology they employ. Some common approaches to achieve long-distance stacking include:

**1. Fiber-Optic Stacking:**
Using<mark style="background: #FFF3A3A6;"> fiber-optic</mark> connections between switches can extend the stacking reach to longer distances. Optical fiber cables are capable of transmitting data over several kilometers with minimal signal degradation, making them suitable for long-distance stacking.

**2. Stacking over MPLS or IP Networks:**
Some advanced stacking technologies allow switches to communicate over MPLS (Multiprotocol Label Switching) or <mark style="background: #FFF3A3A6;">IP (Internet Protocol) </mark>networks. This enables the creation of a virtual stack across geographically dispersed locations connected through a wide-area network (WAN).

**3. Stacking over Dedicated Links:**
In certain cases, dedicated point-to-point links can be established between switches to achieve long-distance stacking. These links might use technologies like leased lines or wireless point-to-point links.

## Switch cascading

**Switch Cascading:**
Switch cascading, also known as "daisy-chaining," is the practice of connecting multiple switches together in a <mark style="background: #FFF3A3A6;">linear or hierarchical manner to expand the number of ports available for network devices</mark>. 

Key characteristics of switch cascading:

1. **Physical Connection:** Switch cascading involves physical <mark style="background: #ADCCFFA6;">connections using regular Ethernet cables</mark> between the switches' Ethernet ports.

2. **Individual Management:** Each switch in the cascaded setup is <mark style="background: #FFF3A3A6;">managed as an individual entit</mark>y. They have <mark style="background: #FFF3A3A6;">separate IP addresses and require individual configurations.</mark>

3. **Limited Performance Improvement:** While cascading allows for more ports, it does not significantly enhance overall network performance. Each switch operates independently, and the traffic is not shared or aggregated between switches.

4. **Limited Scalability:** Cascading has limitations on scalability due to the linear or hierarchical nature of the connections. As more switches are added to the chain, <mark style="background: #FFB8EBA6;">the complexity of the setup and potential points of failure increas</mark>e.

5. **Link Aggregation Limitations:** Traditional cascaded setups may not support advanced link aggregation techniques that combine multiple physical connections into a single logical link.

## Stacking Vs. Cascading

| Concept                | Switch Stacking                    | Switch Cascading                    |
|------------------------|------------------------------------|------------------------------------|
| Physical Connection    | Specialized stacking ports and     | Regular Ethernet ports and         |
|                        | stacking cables or virtual stacking| Ethernet cables                     |
|                        | technology                         |                                    |
| Logical Connection     | Creates a single logical unit     | Operates switches independently    |
|                        | (single IP address for management)| (separate IP addresses for each)   |
| Enhanced Performance   | Aggregates bandwidth and switching| Does not significantly improve     |
|                        | capacity for better performance    | overall network performance        |
| Simplified Management  | Managed as a single entity with   | Each switch requires individual    |
|                        | centralized management            | configuration and management       |
| Scalability            | Easy expansion by adding more     | Limited scalability as complexity  |
|                        | switches to the stack             | increases with more cascaded       |
|                        |                                    | switches                           |
| Link Aggregation       | Supports advanced link aggregation| May have limitations on link       |
|                        | techniques for increased bandwidth| aggregation capabilities            |
| Purpose                | Enhances performance, simplifies  | Expands the number of available   |
|                        | management, and provides          | ports for network devices          |
|                        | scalability                       |                                    |
## Power over Ethernet (PoE)

Power over Ethernet (PoE) is an access layer technology that combines data signals and electrical power into a single Ethernet cable connection to enable remote powered device operation. <mark style="background: #FFF3A3A6;">Using the data signal capabilities, PoE and device status can be monitored, and information shared between a switch and powered device in order to manage the amount of power delivered to the remote device.</mark>

<img width="445" height="233" alt="Pasted image 20230719154737" src="https://github.com/user-attachments/assets/4b8b7c30-13c6-4dfd-a8f4-22bbad54f653" />

| PoE Technology        | IEEE Standard | Max Power Output | Supported Ethernet Speeds | Key Features and Notes                                               |
|-----------------------|---------------|------------------|--------------------------|---------------------------------------------------------------------|
| PoE (802.3af)         | 802.3af       | 15.4W            | 10/100 Mbps              | First standard for PoE; Suitable for low-power devices               |
| PoE+ (802.3at)        | 802.3at       | 30W              | 10/100/1000 Mbps         | Higher power output; Used for devices like IP phones and Wi-Fi APs  |
| PoE++ (802.3bt)       | 802.3bt       | Up to 90W        | 10/100/1000 Mbps         | Provides higher power for demanding devices such as PTZ cameras     |
| UPoE (Cisco)          | Proprietary   | Up to 60W        | 10/100/1000 Mbps         | Cisco's proprietary PoE technology; Offers higher power delivery    |
| 4PPoE (4-pair PoE)    | 802.3bt       | Up to 100W       | 10/100/1000 Mbps         | Utilizes all four pairs of Ethernet cables for increased power      |
| PoE Ultra (Cisco)     | Proprietary   | Up to 60W        | 10/100/1000 Mbps         | Cisco's enhanced PoE technology; Provides higher power delivery     |
| LTPoE++ (802.3bt)     | 802.3bt       | Up to 90W        | 10/100/1000 Mbps         | A Long-Term PoE technology for higher power delivery over 10 years  |
| PoH (Power over HDBaseT) | HDBaseT     | Up to 100W       | Up to 10 Gbps            | Used for AV and video applications over HDBaseT cabling             |

### Power budget
example: https://help.avigilon.com/vma-rpa-4p/en-us/WebUIEdgeOS/EdgeOS_PoE.htm

The PoE (Power over Ethernet) power budget refers to <mark style="background: #BBFABBA6;">the total amount of power available to supply PoE devices in a network</mark>. It represents the maximum power that can be allocated to power devices connected to PoE-enabled network switches or PoE injectors.

In PoE, power is delivered over the Ethernet cables to power devices such as IP phones, wireless access points, IP cameras, and other PoE-enabled devices. The power budget is a critical consideration when designing and deploying a PoE network, as it determines the number and type of PoE devices that can be connected and powered simultaneously.

The PoE power budget is influenced by several factors:

1. **Switch Capacity:** The power budget of a PoE switch depends on its design and power capabilities. PoE switches come in various configurations with different power budgets, usually measured in watts (W). For example, a switch may have a total power budget of 370W or 740W.

2. **PoE Standard:** Different PoE standards (e.g., 802.3af, 802.3at, and 802.3bt) support different power levels. The standard used by the switch and the PoE devices connected to it will determine the power required.

3. **Number and Type of PoE Devices:** The power consumption of PoE devices varies based on their type and PoE standard support. Devices with higher power requirements will consume more of the available power budget.

4. **Port Configuration:** PoE switches usually have specific ports that support PoE. The number of PoE-enabled ports on the switch and the power allocation per port can affect the overall power budget.

It's essential to calculate and manage the PoE power budget carefully to ensure that the total power required by all connected PoE devices does not exceed the available power budget of the switch. If the power budget is exceeded, some PoE devices may not receive adequate power, leading to operational issues or failures.


## Power over HDBaseT (PoH)

[Power Over HDBaseT: Necessity and Applications | FS Community](https://community.fs.com/blog/power-over-hdbaset-necessity-and-applications.html)

Power over HDBaseT (PoH) is a Power over Ethernet (PoE) technology designed specifically for HDBaseT systems. HDBaseT is a connectivity standard that enables the transmission of high-definition video, audio, Ethernet, and control signals over a single category cable (commonly Cat5e, Cat6, or Cat6a).

PoH extends the capabilities of HDBaseT by providing power to the HDBaseT devices, allowing them to be powered directly through the same category cable used for data and video transmission. This eliminates the need for separate power cables and simplifies the installation and setup of HDBaseT systems.

POH technology opens the door for a cost-effective, easy way to deliver power to digital signage in airports, hotels, hospitals, cafeterias or any other environment in need of a video display--eliminating the need for AC power.

Key features and aspects of Power over HDBaseT (PoH):

1. **Power Delivery:** <mark style="background: #FFF3A3A6;">PoH supports power delivery of up to 100 watts (W) over the HDBaseT category cable. </mark>This is significantly<mark style="background: #ADCCFFA6;"> higher power delivery compared to traditional PoE standards like 802.3af (15.4W) and 802.3at (30W).</mark>

2. **HDBaseT Connectivity:** PoH works in conjunction with HDBaseT technology, allowing for the transmission of uncompressed high-definition video, audio, Ethernet, control signals, and power over the same cable.

3. **Single Cable Solution:** By combining data, video, audio, control, and power over a single cable, PoH simplifies installations and reduces cable clutter, making it ideal for applications like audiovisual (AV) installations, digital signage, and video conferencing.

4. **Backward Compatibility:** PoH is backward compatible with standard PoE devices and equipment. It can supply power to HDBaseT devices as well as traditional PoE devices, allowing a mix of PoH and standard PoE devices in the same network.

5. **Extended Reach:** PoH can deliver power and data over longer distances compared to traditional PoE. HDBaseT technology allows for transmission distances of up to 100 meters (328 feet).

6. **Standardization:** PoH is not an official IEEE standard like traditional PoE technologies (e.g., 802.3af, 802.3at, 802.3bt). Instead, it is specific to the HDBaseT Alliance, a consortium of companies promoting the HDBaseT standard.

PoH is commonly used in AV installations, where it simplifies the wiring and power requirements for AV equipment, displays, and projectors. It provides a convenient and efficient solution for delivering power to various devices without the need for separate power outlets or additional power cables, making HDBaseT installations more streamlined and cost-effective.

## HDBaseT 

[What is HDBaseT? - YouTube](https://www.youtube.com/watch?v=ZcovWvme9PQ)

In addition to using a standard RJ45 connector and balanced twisted pair cabling, HDBaseT supports five different specifications. 5Play™ is a term created by HDBaseT Alliance to represent the five features supported over twisted pair cabling:

1. Uncompressed HD video (HD, 3D and 2K/4K)
2. HD audio (Dolby Digital, DTS, Dolby TrueHD and DTS HD-Master Audio)
3. 100BaseT Ethernet
4. Control channel (RS-232, infrared, or USB device)
5. Up to 100 watts of power

## Redundant Power Supply
[What Is a Redundant Power Supply for Network Switch? | FS Community](https://community.fs.com/blog/what-is-a-redundant-power-supply-for-network-switch.html)

A redundant power supply is when a single piece of<mark style="background: #FFF3A3A6;"> networking equipment operates using two or more physical power supplies</mark>. <mark style="background: #FFF3A3A6;">Each of the power supplies will have the capacity to run the device on its own</mark>. This makes sure that the device could operate normally even if one power supply fails. It is usually used in servers and other highly important computers, to minimize the chance of a complete computer shutdown or failure. Now, it is prevailing in many networking devices like network switches as well.

The power supply redundancy could be divided into two types, namely full redundancy and partial redundancy. In full redundancy, every switch is attached to two power supplies, so that if one goes down, the other takes over. This scheme is also called 1:1 redundancy (or 1+1 redundancy sometimes). In partial redundancy, there is one extra power supply for multiple switches. When there is a power failure in your network switch, the power supply needs time switching from one source to another. This is also called 1:N redundancy. Here is the scheme of the two different types of power redundancy:

<img width="643" height="276" alt="Pasted image 20230720133215" src="https://github.com/user-attachments/assets/ecab2474-23e3-421e-a51f-8fc5a7e2c347" />

Normally, the dual power supply in a network switch usually refers to full redundancy. The two power supplies will be powered on and work at the same time. However, in a switch of full redundancy, one power supply may also be idle due to different manufacturers.

### Hot Swapping of power supplies

Normally, network switches with two or more power supplies support hot-swapping. If one of the power supplies stops working, you will typically be<mark style="background: #BBFABBA6;"> able to replace it without taking the device offline</mark>. Equipment that operates using multiple power supplies will allow you to simply unplug the defective power supply and plug a new one physically.

## Energy Efficient Ethernet (EEE)

[Energy Efficient Ethernet Interfaces | Junos OS | Juniper Networks](https://www.juniper.net/documentation/us/en/software/junos/interfaces-ethernet-switches/topics/topic-map/switches-interface-eee.html)

Energy Efficient Ethernet (EEE), an Institute of Electrical and Electronics Engineers (IEEE) 802.3az standard, <mark style="background: #ADCCFFA6;">reduces the power consumption of physical layer devices (PHYs) during periods of low link utilization</mark>. EEE saves energy by switching part of the transmission circuit into <mark style="background: #BBFABBA6;">low power mode when the link is idle</mark>.
<mark style="background: #FFB8EBA6;">An Ethernet link consumes power even when a link is idle</mark>. EEE provides a method to utilize power in such a way that Ethernet links use power only during data transmission. EEE uses a signaling protocol, Low Power Idle (LPI) for achieving the power saving when an Ethernet link is idle. <mark style="background: #FFF3A3A6;">EEE allows PHYs to exchange LPI indications to signal the transition to low power mode when there is no traffic</mark>. <mark style="background: #FFF3A3A6;">LPI indicates when a link can go idle and when the link needs to resume after a predefined delay without impacting data transmission.</mark>

The following copper PHYs are standardized by **IEEE 802.3az**:
- 100BASE-T
- 1000BASE-T
- 10GBASE-T


Key principles and features of Energy Efficient Ethernet (EEE):

1. **Low-Power Idle Mode:** EEE allows network devices to enter a low-power idle state when there is no data activity on the link. This idle mode reduces power consumption significantly, effectively saving energy.
2. **Wake-on-LAN Support:** <mark style="background: #BBFABBA6;">EEE maintains the capability for devices to be woken up remotely using the Wake-on-LAN (WoL) feature, even in low-power idle mode.</mark>
3. **Dynamic Power Adjustment:** EEE enables network devices to dynamically adjust their power consumption based on real-time traffic conditions. When traffic increases, devices can quickly return to full power mode to handle the increased workload.
4. **Link Partner Detection:** EEE requires communication between link partners (e.g., switches and NICs) to negotiate and synchronize low-power idle modes, ensuring compatibility between devices.
5. **Transmit and Receive Power Adjustment:** <mark style="background: #FFF3A3A6;">Both the transmit (TX) and receive (RX) sides of the link can enter low-power idle modes independently, allowing for further power savings.</mark>
6. **Automatic Power Recovery:** When data activity resumes on the link, EEE allows devices to quickly and automatically return to full power mode without causing any significant delays.

EEE can help organizations meet energy efficiency requirements and comply with environmental regulations that promote energy conservation.

## VLAN
[Virtual LAN (VLAN) - Scaler Topics](https://www.scaler.com/topics/vlan/)
[https://packetlife.net/media/library/20/VLANs.pdf](https://packetlife.net/media/library/20/VLANs.pdf)

VLAN stands for Virtual Local Area Network. It is a network technology that allows you to <mark style="background: #BBFABBA6;">logically divide a physical network into multiple virtual segments</mark>, each operating as its own independent network. VLANs are created to improve network performance, security, and management by <mark style="background: #FFF3A3A6;">segmenting network traffic into separate broadcast domains</mark>.

<img width="407" height="301" alt="Pasted image 20230720140235" src="https://github.com/user-attachments/assets/645d73cc-3ec1-4a0f-a1c0-76ed9938bb88" />

Key points about VLANs:

1. **Logical Segmentation:** VLANs provide logical segmentation of a physical network, allowing devices in different VLANs to communicate as if they were on separate physical networks.
2. **Broadcast Isolation:** Devices within the same VLAN can communicate with each other directly, but broadcast traffic is isolated to the VLAN, <mark style="background: #FFF3A3A6;">reducing unnecessary network traffic and potential broadcast storms</mark>.
3. **Security:** VLANs can <mark style="background: #FFF3A3A6;">enhance network security by separating sensitive or critical data traffic from less secure segments</mark>, preventing unauthorized access to certain parts of the network.
4. **Performance Optimization:** VLANs can be used to group devices based on their traffic patterns, helping to optimize network performance and reduce congestion.
5. **Flexibility and Scalability:** VLANs provide flexibility in network design, <mark style="background: #FFF3A3A6;">allowing administrators to reconfigure and expand the network easily without the need to physically rewire the infrastructure.</mark>
6. **VLAN Tagging:** To identify VLAN membership, a VLAN tag (also known as a VLAN ID or VID) is added to each Ethernet frame, indicating which VLAN the frame belongs to. VLAN tagging is a fundamental requirement for VLAN implementation.

Types of VLANs:

1. **Port-based VLAN:** Devices are assigned to VLANs based on the physical switch port they are connected to. <mark style="background: #FFF3A3A6;">All devices connected to the same port are part of the same VLAN</mark>.

2. **MAC Address-based VLAN:** <mark style="background: #FFF3A3A6;">Devices are assigned to VLANs based on their MAC addresses</mark>. This type of VLAN is <mark style="background: #FFB8EBA6;">less common</mark> and is usually used in specific scenarios.

3. **802.1Q VLAN (Tagged VLAN):** The IEEE 802.1Q standard introduces VLAN tagging, where <mark style="background: #BBFABBA6;">a VLAN ID is added to the Ethernet frame's header</mark>. This allows switches to identify which VLAN the frame belongs to, enabling devices on different switches to be part of the same VLAN.

> NOTE: Tag protocol identifier (TPID)
> A 16-bit field set to a value of 0x8100[b] in order to identify the frame as an IEEE 802.1Q-tagged frame. This field is located at the same position as the EtherType field in untagged
> frames, and is thus used to distinguish the frame from untagged frames.
> 

### Advantages

VLANs (Virtual Local Area Networks) offer numerous advantages and benefits that make them an essential tool for network administrators. Some of the key advantages of VLANs include:

1. **Network Segmentation:** VLANs allow the logical segmentation of a single physical network into multiple virtual networks. This helps isolate traffic and reduces the broadcast domain size, leading to better network performance and management.

2. **Enhanced Security:** VLANs provide improved network security by isolating sensitive data and critical resources from other parts of the network. Devices in one VLAN cannot directly communicate with devices in another VLAN unless explicitly allowed, reducing the risk of unauthorized access and data breaches.

3. **Broadcast Control:** VLANs confine broadcast traffic within their own broadcast domain, preventing broadcast storms and reducing unnecessary network traffic. This helps maintain network efficiency and stability.

4. **Simplified Network Management:** By logically grouping devices with similar functions or requirements into VLANs, <mark style="background: #FFF3A3A6;">network management becomes more straightforwar</mark>d. VLANs allow network administrators to apply consistent policies and configurations to devices within the same VLAN.

5. **Flexibility and Scalability:** VLANs enable network administrators to reconfigure and expand the network without the need to physically rewire the infrastructure. This flexibility makes it easier to accommodate changes in network requirements and add new devices or departments to the network.

6. **Optimized Network Performance:** VLANs can be used to prioritize traffic and allocate network resources more efficiently. Devices with specific performance requirements, such as voice or video conferencing, can be placed in separate VLANs and given higher priority for bandwidth, ensuring optimal performance.

7. **Improved Resource Sharing:** <mark style="background: #FFF3A3A6;">VLANs can help in resource sharing by allowing multiple departments or user groups to access shared resources such as printers, servers, or network-attached storage devices securely and efficient</mark>ly.

8. **Cost-Efficient Network Design:** VLANs reduce the need for physical network segmentation, such as deploying separate switches for different groups of devices. This results in cost savings and more efficient use of network infrastructure.

9. **Support for Virtualization:** In virtualized environments, VLANs are used to isolate virtual machines (VMs) on the same physical server, providing network security and efficient use of network resources within the virtual environment.

10. **Compliance and Regulatory Requirements:** VLANs aid in meeting regulatory requirements for data segregation and privacy, as they offer a controlled environment for sensitive data.

### Disadvantages

While VLANs offer significant advantages, they also come with certain disadvantages and challenges that network administrators should be aware of:

1. **Complex Configuration:** <mark style="background: #FFB8EBA6;">Setting up VLANs and managing their configurations can be complex</mark>, especially in large and dynamic network environments. Improper configuration can lead to miscommunication between VLANs or security vulnerabilities.

2. **VLAN Spanning:** In some cases, VLANs may need to span multiple switches or network segments. This can introduce additional complexities and require careful management to maintain proper VLAN communication and segmentation. When VLANs are numerous and significant, the network may struggle to manage the<mark style="background: #FFB8EBA6;"> spanning tree structures required to avoid traffic loop</mark>s.

3. **Resource Overhead:** Implementing VLANs requires network switches that support VLAN tagging and management. For very small networks, the additional cost of VLAN-capable switches may not be justified.

4. **Broadcast Flooding:** If VLANs are not appropriately configured, broadcast traffic from one VLAN can potentially flood other VLANs, leading to network performance issues.

5. **Potential for Misconfiguration:** Misconfiguring VLANs can result in unintended consequences, such as communication issues between devices or compromised network security. Proper documentation and thorough testing are essential when making changes to VLAN configurations.

6. **Increased Administrative Overhead:** Managing multiple VLANs and ensuring proper traffic separation may require more effort and expertise from network administrators.

7. **Troubleshooting Complexity:** When issues arise in a network with multiple VLANs, identifying the source of the problem and troubleshooting can be more challenging due to the increased complexity of the network design.

8. **VLAN Hopping Attacks:** If VLANs are not adequately protected, there is a risk of VLAN hopping attacks, where an attacker gains unauthorized access to traffic on other VLANs. [VLAN Hopping - N10-008 CompTIA Network+ : 4.2 - YouTube](https://www.youtube.com/watch?v=pDumMKDK4Wc&t=3s)

9. **Resource Constraints:** In certain scenarios, such as very large <mark style="background: #FFB8EBA6;">networks with numerous VLANs, there may be resource constraints on switches or routers</mark>. Ensuring that the network infrastructure can handle the increased demands is essential.

10. **Compatibility with Legacy Devices:** Some older or<mark style="background: #FFB8EBA6;"> non-VLAN-aware devices may not be compatible with VLANs</mark>, limiting their usability within a VLAN-segmented network.

Additionally: 
1. One downside of VLANs is the <mark style="background: #FFB8EBA6;">limitation of 4,096 VLANs per switching domain in a modern data center or cloud infrastructure</mark>. A single network segment can host tens of thousands of systems and hundreds or thousands of separate tenant organizations, each of which may require tens or hundreds of VLANs. Where VXLAN is required.

### Tagged VLAN ( **802.1Q)

Tagged VLAN, also known as IEEE 802.1Q or VLAN tagging, is a technique used to identify and distinguish different VLANs on a network. It is an essential feature in modern Ethernet networks, <mark style="background: #FFF3A3A6;">allowing multiple VLANs to coexist and traverse a single physical network infrastructure.</mark>

In traditional Ethernet networks, devices within the same VLAN share the same broadcast domain and do not require VLAN tags. However, when multiple VLANs need to be transmitted over the same physical network, it becomes necessary to differentiate the VLAN traffic to ensure proper segregation and communication between VLANs.

Here's how tagged VLANs (802.1Q) work:

1. **VLAN Tagging:** When a frame from a device on a VLAN needs to traverse a network, it is tagged with additional information called a VLAN tag. This VLAN tag includes a VLAN identifier (VLAN ID), which indicates the VLAN to which the frame belongs. 

| VLAN ID | Common Uses                                                     |
|---------|-----------------------------------------------------------------|
| 0       | Default VLAN (often used for untagged frames, also called PVID)|
| 1       | Default VLAN (older implementations or as a management VLAN)    |
| 2       | Reserved (Cisco default VLAN)                                   |
| 3-4     | Reserved                                                        |
| 5       | Reserved (Cisco Discovery Protocol)                             |
| 6-9     | Reserved                                                        |
| 10      | Reserved (FDDI default VLAN)                                    |
| 11-1001 | Available for general use                                       |
| 1002    | Default VLAN (Cisco default VLAN for FDDI and Token Ring)       |
| 1003    | Default VLAN (Cisco default VLAN for FDDI and Token Ring)       |
| 1004-1005 | Reserved (Cisco default VLANs for Token Ring)                  |
| 1006-1023 | Available for general use                                      |
| 1024-2047 | Reserved (Cisco)                                               |
| 2048-4094 | Available for general use                                      |
| 4095    | Reserved (reserved for special purposes, often used as a "discard VLAN")  |
| 4096    | Reserved (invalid VLAN ID)                                     |

Please note that the usage of VLAN IDs can vary depending on the specific networking equipment and configurations in use. VLANs 1 and 1002-1005 are often considered reserved or reserved for specific purposes in Cisco networking environments. Always refer to the documentation of your networking equipment and follow best practices when assigning VLAN IDs.

2. **Ethernet Frame Format:** The VLAN tag is inserted into the Ethernet frame's header, specifically within the 802.1Q tag field. The VLAN tag includes a 4-byte header, with the VLAN ID being a 12-bit field, allowing for up to 4,096 different VLANs (IDs 0 to 4095).<img width="403" height="231" alt="Pasted image 20230720140044" src="https://github.com/user-attachments/assets/5da029aa-ff55-418e-aba5-40e0e8df6b74" /><img width="802" height="205" alt="Pasted image 20230720160506" src="https://github.com/user-attachments/assets/2ec12b2e-ad9a-4331-9846-f52bf73766e0" />



3. **Tagged and Untagged Ports:** Ports on network switches can be configured to be either "tagged" or "untagged" for specific VLANs. <mark style="background: #FFF3A3A6;">Ports assigned as "untagged" are members of a specific VLAN and do not carry a VLAN tag in the Ethernet frames they receive and send</mark>. <mark style="background: #BBFABBA6;">Ports assigned as "tagged" are configured to allow frames from multiple VLANs and add VLAN tags to the frames as they pass through the switch.</mark>

4. **Switch Trunk Ports:** To carry frames with VLAN tags between switches, trunk ports are used. <mark style="background: #FFF3A3A6;">Trunk ports are configured to accept frames from multiple VLANs and transmit them with VLAN tags intact</mark>. Trunk ports are essential for inter-switch communication when multiple VLANs are involved.  <img width="652" height="192" alt="Pasted image 20230720155424" src="https://github.com/user-attachments/assets/200865bf-6a33-435b-91af-55fea7ba7bcc" />
[Switch stacking vs switch trunking vs switch uplink | FS Community](https://community.fs.com/blog/switch-stacking-vs-trunking-vs-uplink-which-is-best-to-connect-switches.html)

5. **Interoperability:** To maintain interoperability between devices and <mark style="background: #FFF3A3A6;">switches that do not support VLAN tagging, frames sent to non-VLAN-aware devices or devices in the native VLAN are sent untagged.</mark> This is called the "native VLAN" or "PVID" (Port VLAN ID), <mark style="background: #FFF3A3A6;">which is a default VLAN for untagged frames on a VLAN-aware switch port.</mark>

Benefits of Tagged VLANs (802.1Q):

- **Efficient VLAN Segmentation:** Tagged VLANs allow multiple VLANs to use the same physical network infrastructure, optimizing network resources and reducing the need for separate physical LANs.

- **Scalability:** With 4,096 available VLAN IDs, IEEE 802.1Q offers significant scalability for even the most complex network environments.

- **Flexibility:** Tagged VLANs provide flexibility in network design, as devices can be dynamically assigned to different VLANs by configuring switch ports.

- **Improved Network Security:** VLAN tagging enhances network security by segregating traffic and preventing unauthorized access to data between VLANs.

- **Virtualization Support:** <mark style="background: #BBFABBA6;">VLAN tagging is commonly used in virtualized environments to segregate and prioritize traffic between virtual machines (VMs) on the same physical server.</mark>

Tagged VLANs (802.1Q) are widely used in modern networking to provide efficient network segmentation, security, and flexibility in managing complex network environments.

### Untagged VLAN

An untagged VLAN, also known as an access VLAN or native VLAN, is a Virtual Local Area Network that does not have an associated VLAN tag in its Ethernet frames. In other words, frames from devices assigned to the untagged VLAN do not include a VLAN tag in their header when transmitted over the network.

Here's how untagged VLANs work:

1. **Port Configuration:** On a network switch, individual switch ports can be assigned to specific VLANs. <mark style="background: #FFF3A3A6;">Ports that are assigned to an untagged VLAN are considered "access ports" for that VLAN.</mark>

2. **VLAN Membership:** Devices connected to an access port automatically become members of the untagged VLAN associated with that port.

3. **Frame Transmission:** When a device sends Ethernet frames through an access port assigned to an untagged VLAN, the frames are transmitted without any VLAN tag. This is because the frames are part of the untagged VLAN, and the switch assumes that untagged frames belong to the VLAN associated with that access port.

4. **Receiving Frames:** When the switch receives frames from devices on access ports, it knows which VLAN the frames belong to based on the port's VLAN assignment. The switch treats these frames as part of the untagged VLAN.

5. **Native VLAN:** The untagged VLAN on a trunk port (a port that carries traffic from multiple VLANs) is often referred to as the "native VLAN" or "PVID" (Port VLAN ID). Frames from the native VLAN are sent untagged over the trunk link, and the receiving switch understands that untagged frames belong to the native VLAN.

Common uses of Untagged VLANs:

1. **End-User Devices:** End-user devices like computers, printers, IP phones, and cameras are typically connected to access ports assigned to untagged VLANs. These devices are generally unaware of VLANs and do not include VLAN tags in their frames.

2. **Network Segmentation:** <mark style="background: #BBFABBA6;">Untagged VLANs are used to logically segment a network into separate broadcast domains without requiring VLAN-aware devices</mark>. Each access port is associated with a specific untagged VLAN, effectively separating the connected devices into different VLANs.

3. **Guest Networks:** <mark style="background: #BBFABBA6;">In environments where guest access is provided, an untagged VLAN can be used to segregate guest devices from the main network, limiting their access to certain resources.</mark>

4. **Legacy Devices:** <mark style="background: #BBFABBA6;">Some older network devices or equipment may not support VLAN tagging. In such cases, untagged VLANs can be used to integrate these devices into the VLAN architecture.</mark>

It's important to note that untagged VLANs are specific to the access port configuration and are generally used in small-scale networks or in scenarios where devices are not VLAN-aware. For inter-switch communication between VLANs, VLAN tagging (802.1Q) on trunk ports is essential.

### Tagged VLAN vs. Untagged VLAN

 > Tagged VLAN is called “trunk” and Untagged one is called “access”.

Untagged or “access” VLANs are connected to hosts (usually servers) that pass VLAN information to and from each network and cannot differentiate between any VLAN configuration. In this way, <mark style="background: #BBFABBA6;">untagged VLANs have a more linear structure, moving from A to B rather than from A to B, C, and D. Generally, untagged VLANs are the default.</mark>

Here’s how the flow of a untagged VLAN packet:

1. Host A sends traffic to a switch, and the traffic doesn’t have a VLAN tag.
2. Traffic is received on access port 1 (also untagged).
3. Port 1 adds a VLAN tag to the frame, and the switch dictates that the frame must be sent to Host B through access port 2 (an untagged port).
4. The VLAN tag is removed.
5. Traffic flows to Host B.

In case of a Tagged VLAN the flow is below:
1. Host A sends a frame without a VLAN tag.
2. Traffic is received on port 1 that is configured with VLAN 7, which gets added to the frame.
3. <mark style="background: #FFF3A3A6;">The switch recognizes the VLAN tag, which says to send the frame to switch 2.</mark>
4. Switch 2 has a tagged access port for VLAN 7, which matches the original tag.
    1. If at this point, VLAN tags did not match (i.e., VLAN 7 vs. VLAN 5), the frame gets dropped.
5. Traffic is forwarded on to the switch 2 tagged port, which, again, checks whether the tag is permitted elsewhere and distributes the broadcast to all other VLAN 7-configured access ports.
6. Once traffic reaches an untagged access port, the tag is stripped from the frame, which<font color="#0f243e"> is sent to the final host.</font>

### Native VLAN

When an Ethernet frame is transmitted over a trunk port, it may or may not have a VLAN tag. Frames without VLAN tags are considered untagged frames. The native VLAN is the VLAN to which untagged frames on a trunk port belong. It is often assigned to the trunk port as a default or used for certain specific purposes.

Key points about the native VLAN:

1. **Untagged Frames:** Untagged frames are transmitted over a trunk port without a VLAN tag in the Ethernet frame's header. These frames are intended for devices that are not VLAN-aware or do not support VLAN tagging.

2. **Default VLAN:** The native VLAN is often assigned as the default VLAN on a trunk port. Frames that do not have a VLAN tag are associated with the native VLAN by default.

3. **Configuration Flexibility:** Administrators have the flexibility to choose which VLAN should be the native VLAN on a trunk port. It can be set to any specific VLAN depending on the network's requirements.

4. **Interoperability:** The native VLAN is essential for ensuring interoperability with devices that are not VLAN-aware or do not support VLAN tagging. It allows such devices to communicate with the rest of the VLANs on the network.

5. **Security Considerations:** The native VLAN should be chosen carefully to avoid potential security risks. Frames in the native VLAN can be subject to attacks like VLAN hopping if proper security measures are not in place.

<mark style="background: #FFF3A3A6;">It's important to note that the native VLAN is relevant only on trunk ports</mark>. Access ports, which are used to connect end-user devices and do not carry traffic for multiple VLANs, do not have a native VLAN concept since they expect all frames to be tagged with the appropriate VLAN ID.

practical use case: [Voice VLAN - Auxiliary VLAN – What exactly are they? – Practical Networking .net](https://www.practicalnetworking.net/stand-alone/voice-vlan-auxiliary-vlan/)


### Important Links

VLAN: [Virtual Local Area Networks (VLANs) – Practical Networking .net](https://www.practicalnetworking.net/stand-alone/vlans/https://www.practicalnetworking.net/stand-alone/vlans/)
Routing b/w VLANS: [Routing Between VLANs & Layer 3 Switches – Practical Networking .net](https://www.practicalnetworking.net/stand-alone/routing-between-vlans/)
Native VLANS:  [Native VLAN - the DEFINITIVE illustration - YouTube](https://www.youtube.com/watch?v=Fmq1E1Qr2W4)
configure: [Configuring VLANs on Cisco Switches – Practical Networking .net](https://www.practicalnetworking.net/stand-alone/configuring-vlans/)


## sFLOW

[What Is sFlow? How Does It Monitor Network Traffic? - Huawei](https://info.support.huawei.com/info-finder/encyclopedia/en/sFlow.html)
[SFlow vs SNMP vs NetFlow: What Are the Differences? | FS Community](https://community.fs.com/blog/sflow-vs-snmp-vs-netflow.html)
[https://sflow.org/sFlowOverview.pdf](https://sflow.org/sFlowOverview.pdf)
[Noction Flow Analyzer - Simple, Fast and Super Affordable](https://www.noction.com/flow-analyzer)

Sampled Flow (sFlow) is a<mark style="background: #FFF3A3A6;"> traffic monitoring technology that collects traffic statistics by sampling packets and analyzes the traffic statistics</mark>. sFlow analyzes traffic on a per-interface basis to monitor traffic in real time, detect abnormal traffic, and locate the source of attack traffic in a timely manner, greatly facilitating routine inspection and maintenance for enterprises.
<img width="919" height="425" alt="Pasted image 20230808204945" src="https://github.com/user-attachments/assets/7beb66a6-071f-45f5-9ab9-24775c093b0a" />


## VXLAN

VXLAN, which stands for Virtual Extensible LAN, is a network <mark style="background: #BBFABBA6;">virtualization technology used to extend and scale Layer 2 (L2) networks across physical network boundaries</mark>. It was developed to address the challenges of traditional VLAN-based networks, such as limited scalability, large broadcast domains, and the need for manual configuration.

VXLAN is widely used in cloud computing environments, especially within data centers, where it helps address the challenges of virtual machine mobility, network scalability, and the need for a more flexible and dynamic network infrastructure. It has become a popular choice for building overlay networks and simplifying network management in modern data center architectures.

Key features and concepts of VXLAN:

1. **Overlay Network:** VXLAN creates an overlay network on top of an existing IP network infrastructure.<mark style="background: #FFF3A3A6;"> It encapsulates Ethernet frames with an additional VXLAN header, allowing virtual machines (VMs) and network segments to be decoupled from the underlying physical network.</mark>
    
2. **VXLAN Tunneling:** VXLAN <mark style="background: #BBFABBA6;">encapsulates L2 Ethernet frames within UDP packets,</mark> which can be transmitted over an IP network (IPv4 or IPv6). This process is known as VXLAN tunneling.
    
3. **VXLAN Header:** The VXLAN header includes information such as the VXLAN Network Identifier (VNI), which acts as a VXLAN segment identifier and helps differentiate between multiple VXLAN segments within the same physical network.
    
4. **VXLAN VNI:** The VXLAN Network Identifier (VNI) allows <mark style="background: #BBFABBA6;">VXLAN to support a large number of virtual segments (up to 16 million)</mark> compared to the limited number of VLANs (4094) available in traditional Ethernet networks.
    
5. **Multicast or Unicast:** VXLAN can use either multicast or unicast for traffic forwarding, depending on the network infrastructure and design.
    
6. **Overlay Gateway (VTEP):** Devices that participate in VXLAN are known as VXLAN Tunnel Endpoints (VTEPs). They are responsible for encapsulating and de-encapsulating VXLAN frames and bridging traffic between VXLAN segments and the physical network.
    
7. **Network Virtualization:** VXLAN enables network virtualization and allows VMs to be easily moved and distributed across different physical hosts without reconfiguring the underlying network infrastructure.
    
8. **Network Segmentation:** VXLAN facilitates network segmentation, enabling logical isolation and better control over traffic flow in large data center environments.
    
9. **Compatibility:** VXLAN can work across different vendor equipment and is supported by various network hardware and software.
