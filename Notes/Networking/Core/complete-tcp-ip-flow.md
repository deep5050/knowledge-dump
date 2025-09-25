Here's the complete flow of HTTP data from userspace to physical transmission, highlighting the key TCP/IP functions:

## Userspace to Kernel Transition

**Application Layer**:
```
HTTP application calls write()/send() → sys_sendto()/sys_write()
```
- User process makes system call to send HTTP data
- Kernel entry point: `sys_sendto()` or `sys_write()`

## Socket Layer

**`sys_sendto()` → `sock_sendmsg()`**:
- Socket layer entry point
- Determines socket type (TCP in this case)
- Calls protocol-specific send function

**`sock_sendmsg()` → `inet_sendmsg()` → `tcp_sendmsg()`**:
- `inet_sendmsg()`: Internet protocol family handler
- **`tcp_sendmsg()`**: Core TCP function that:
  - Copies data from userspace to kernel buffers
  - Manages TCP send buffer
  - Handles flow control and congestion control
  - Creates TCP segments

## TCP Layer Processing

**`tcp_sendmsg()` → `tcp_push()`**:
- **`tcp_push()`**: Forces transmission of queued data
- Calls `__tcp_push_pending_frames()`

**`__tcp_push_pending_frames()` → `tcp_write_xmit()`**:
- **`tcp_write_xmit()`**: Main TCP transmission function
- Handles TCP congestion control
- Manages TCP window size
- Creates individual TCP segments
- Calls `tcp_transmit_skb()` for each segment

**`tcp_transmit_skb()`**:
- Adds TCP header to the segment
- Calculates TCP checksum
- Handles TCP options
- Calls `ip_queue_xmit()` to pass to IP layer

## IP Layer Processing

**`ip_queue_xmit()`**:
- Performs routing lookup to determine outgoing interface
- Adds IP header to the packet
- Sets IP header fields (TTL, protocol, etc.)
- Calls `ip_local_out()`

**`ip_local_out()` → `__ip_local_out()`**:
- **`__ip_local_out()`**: Core IP output function
- Triggers netfilter hook `NF_INET_LOCAL_OUT`
- iptables OUTPUT chain rules are processed here
- Calls `dst_output()` on successful completion

**`dst_output()` → `ip_output()`**:
- **`ip_output()`**: Main IP output processing
- Handles IP fragmentation if needed
- Triggers `NF_INET_POST_ROUTING` netfilter hook (NAT happens here)
- Calls `ip_finish_output()`

**`ip_finish_output()` → `ip_finish_output2()`**:
- Final IP layer processing
- Transitions to link layer

## Link Layer Resolution

**`ip_finish_output2()` → `neigh_output()`**:
- **`neigh_output()`**: Neighbor subsystem entry
- Performs ARP resolution for MAC address lookup
- If MAC address known: proceeds immediately
- If unknown: queues packet and sends ARP request

**`neigh_output()` → `neigh_hh_output()`**:
- **`neigh_hh_output()`**: Hardware header caching
- Adds Ethernet header with source/destination MAC addresses
- Calls `dev_queue_xmit()`

## Network Device Layer

**`dev_queue_xmit()`**:
- Network device transmission entry point
- Selects appropriate TX queue (for multi-queue devices)
- Applies traffic control (tc) rules if configured
- Handles network device queuing
- Calls `__dev_xmit_skb()`

**`__dev_xmit_skb()` → `sch_direct_xmit()`**:
- **`sch_direct_xmit()`**: Direct transmission path
- Bypasses queueing disciplines if possible for better performance
- Calls `dev_hard_start_xmit()`

**`dev_hard_start_xmit()`**:
- Calls the network device driver's transmit function
- Function pointer: `netdev->netdev_ops->ndo_start_xmit`

## Ethernet Driver Layer

**Driver-Specific `ndo_start_xmit()` (e.g., `e1000_xmit_frame()`, `igb_xmit_frame()`)**:
- Allocates DMA buffers
- Maps packet data for DMA transfer
- Sets up hardware TX descriptors
- Programs hardware registers
- Triggers hardware transmission

## Hardware/PHY Layer

**Hardware Controller**:
- DMA engine transfers data from system memory
- Hardware adds preamble, start frame delimiter
- Calculates and adds Frame Check Sequence (FCS)
- Serializes data for transmission

**PHY Transmission**:
- Converts digital data to analog signals
- Transmits electrical signals over copper/fiber
- Handles physical layer encoding (Manchester, 4B5B, etc.)

## Complete Flow Summary

```
HTTP App → write()/send() → sys_sendto() → sock_sendmsg() → 
inet_sendmsg() → tcp_sendmsg() → tcp_push() → 
__tcp_push_pending_frames() → tcp_write_xmit() → 
tcp_transmit_skb() → ip_queue_xmit() → ip_local_out() → 
__ip_local_out() → [NF_INET_LOCAL_OUT] → dst_output() → 
ip_output() → [NF_INET_POST_ROUTING] → ip_finish_output() → 
ip_finish_output2() → neigh_output() → neigh_hh_output() → 
dev_queue_xmit() → __dev_xmit_skb() → sch_direct_xmit() → 
dev_hard_start_xmit() → ndo_start_xmit() → Hardware DMA → PHY
```

## Key Points

- **`tcp_sendmsg()`**: Where userspace data enters TCP stack
- **`tcp_transmit_skb()`**: Creates actual TCP segments with headers
- **`ip_queue_xmit()`**: Routing and IP header addition
- **`__ip_local_out()`**: Netfilter integration point
- **`neigh_output()`**: ARP resolution and MAC header addition
- **`dev_queue_xmit()`**: Device driver interface

Each layer adds its own headers and performs protocol-specific processing while maintaining clear separation of concerns in the network stack architecture.
