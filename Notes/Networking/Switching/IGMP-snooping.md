<img width="720" height="320" alt="image" src="https://github.com/user-attachments/assets/f7b45543-036c-46da-955d-de871ae93400" />

> IPv4 multicast address (224.0.0.0 - 239.255.255.255)

## IGMP Snooping in a Switch

<b>IGMP snooping</b> is a network switch feature that helps manage multicast traffic efficiently. It allows the switch to listen to Internet Group Management Protocol (IGMP) messages exchanged between hosts and routers. By doing so, the switch can learn which devices are interested in receiving multicast traffic and forward that traffic only to those devices, rather than flooding it to all ports.

### How IGMP Snooping Works

1. **Listening to IGMP Messages**: The switch monitors IGMP messages sent by hosts to join or leave multicast groups.
2. **Building a Multicast Group Table**: Based on the IGMP messages, the switch creates a table that maps multicast group addresses to the ports where interested hosts are connected.
3. **Traffic Forwarding**: When multicast traffic is received, the switch checks its table and forwards the traffic only to the relevant ports, reducing unnecessary load on the network.

### Benefits of IGMP Snooping

- **Reduced Bandwidth Usage**: By limiting multicast traffic to only those ports that need it, IGMP snooping minimizes unnecessary bandwidth consumption.
- **Improved Network Performance**: It enhances overall network performance by reducing the amount of broadcast traffic.
- **Efficient Resource Utilization**: Devices that do not need multicast traffic do not receive it, allowing them to use their resources more effectively.

### Considerations

- **Configuration**: IGMP snooping must be enabled on the switch, and it may require additional configuration depending on the network setup.
- **Compatibility**: Ensure that all devices in the network support IGMP snooping for optimal performance.

In summary, IGMP snooping is a valuable feature for managing multicast traffic in a network, leading to more efficient use of resources and improved performance.
