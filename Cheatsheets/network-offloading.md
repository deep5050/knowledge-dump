Refer to this document instead: [chevallier-network-classification-offload.pdf](https://github.com/user-attachments/files/22057923/chevallier-network-classification-offload.pdf)

https://bootlin.com/blog/multi-queue-improvements-in-linux-kernel-ethernet-mvneta/
https://ntk148v.github.io/posts/linux-network-performance-ultimate-guide/

# Overview

Offloading network traffic classification to hardware means delegating the work of inspecting packet headers and making forwarding or filtering decisions to the network interface card (NIC) itself rather than to the CPU.  Instead of routing every packet through the Linux Traffic Control (TC) subsystem in software, the kernel programs flow‐matching rules directly into the NIC’s classification engine.  Packets that hit a hardware rule are then steered, dropped, or queued without further CPU intervention.

---

## Packet Path with Hardware Offload

1. Frame arrival  
   - A frame comes in over the PHY and is handed to the MAC layer.  
   - The MAC’s packet processor applies any MAC‐level offloads (e.g., VLAN tagging, checksum checks).  

2. Hardware classification  
   - The NIC examines L2/L3/L4 header fields against a preconfigured flow table (often implemented in TCAM or hashed flow tables).  
   - If the packet matches a hardware rule, the NIC executes the associated action: drop, redirect to a specific RX queue, mirror, or apply rate limits.

3. DMA and interrupt  
   - The (possibly modified) packet is DMA‐transferred to system memory.  
   - The NIC raises an interrupt tied to the RX queue that the packet landed in.  
   - Because flows are pinned to specific queues and CPUs, cache locality is improved and the kernel softirq processing is streamlined.

---

## Configuration Workflow

1. Enable classification offloads on the interface:  
   ```bash
   ethtool --features eth0 hw-tc-offload on
   ```

2. Attach TC “flower” filters with the offload flag:  
   ```bash
   tc qdisc add dev eth0 clsact
   tc filter add dev eth0 ingress \
       flower \
       src_ip 10.0.0.1/32 dst_ip 10.0.0.2/32 \
       action pass \
       skip_sw \
       humatch in_hw
   ```
   - `skip_sw` tells the kernel not to install a redundant software rule.  
   - `in_hw` instructs the kernel to hand the rule to the device driver for hardware programming.

3. Driver translation  
   - The NIC driver implements TC offload callbacks (`ndo_setup_tc`) that translate the generic TC flower rule into vendor‐specific hardware commands (e.g., TCAM entries, hash‐table keys).

4. Rule programming  
   - The driver uses device‐specific APIs (often via `ethtool` or direct firmware calls) to program the NIC’s classification hardware.  
   - Once installed, the hardware table lives on the NIC and persists across interrupts.

---

## Benefits and Use Cases

| Benefit                 | Description                                                                 |
|-------------------------|-----------------------------------------------------------------------------|
| CPU offload             | Frees CPU cycles by avoiding per‐packet software inspections.               |
| Lower latency           | Packets are acted on faster since they bypass parts of the kernel stack.    |
| Traffic steering        | Directs flows to specialized Rx queues or dedicated cores for parallelism. |
| Filtering and policing  | Hardware‐enforced drop or rate‐limit avoids CPU‐side bursts.                |

Use cases include DDoS mitigation, fine‐grained QoS, accelerated container networking, and secure flow isolation in multi‐tenant environments.

---

## Under the Hood: NIC Classification Engines

Most modern NICs expose a match‐action pipeline comprising:

- **Exact‐match hash tables** for 5‐tuple unicast flows  
- **TCAM** blocks for wildcard or masked‐field rules (e.g., subnets, protocols)  
- **Action units** capable of rewriting headers, steering queues, or dropping  
- **Metering/rate‐limiters** for policing traffic on a per‐flow basis  

When the kernel hands over a flower rule, the driver allocates table entries, configures matches/masks, and links the entry to the desired action block.  Hardware then automatically processes every incoming packet against those entries in real time.

---


## Next‐Generation Offloads

- **eBPF offload**: Loading BPF programs directly to NICs with programmable data planes (P4, XDP offloads).  
- **Netfilter hardware acceleration**: Pushing iptables/nftables rulesets into hardware for even deeper packet inspection.  
- **SmartNICs**: Full-blown ARM or RISC cores on the NIC for stateful flow processing at line rate.

These trends point to ever-richer hardware classification, enabling Linux to scale to tens or hundreds of millions of flows per second without CPU bottlenecks.

---

# What Is an RX Queue?

An RX (receive) queue is a dedicated hardware pathway on a NIC for delivering incoming packets to the host. Each queue consists of a ring buffer of descriptors that point to pre-allocated memory buffers. When a packet arrives and is classified (either by hardware offload or software), the NIC places it into one of these RX queues for the kernel to process.

---

## Why Multiple RX Queues Matter

- Parallelism  
  Modern NICs offer many RX queues (often 8, 16, or more) so different flows can be steered to separate queues. This lets multiple CPU cores process packets concurrently without contention.  

- Cache Locality  
  By pinning each RX queue to a particular CPU (via IRQ affinity or Receive Side Scaling), the packets and their metadata stay in that core’s cache, reducing memory churn.  

- Load Distribution  
  Hardware classifiers can hash flows across queues (RSS) or use explicit rules (TC offload) to balance traffic, preventing hotspots on any single core.

---

## Lifecycle of a Packet in an RX Queue

1. Buffer Allocation  
   The driver pre-allocates a pool of sk_buff or XDP buffers and assigns them to RX descriptors.  

2. Packet Arrival  
   Once classified, the NIC writes the packet into the assigned buffer and updates the queue’s descriptor.  

3. Interrupt or Poll  
   - In interrupt mode, the NIC raises a queue-specific interrupt.  
   - With NAPI polling, the kernel periodically polls each RX queue to pull batches of packets, minimizing overhead under high load.  

4. SKB or XDP Processing  
   The driver hands the packet buffer to the networking stack (as an sk_buff) or to an XDP program if configured.

---

## RX Queues & Hardware Offload

When you offload classification rules:

- The NIC tags each flow with a queue index.  
- Matching packets bypass generic dispatch logic and land directly in the queue tied to your chosen CPU or processing pipeline.  
- This direct path slashes latency and avoids software queue shuffling.

---

<img width="723" height="704" alt="image" src="https://github.com/user-attachments/assets/ef779606-21ff-4481-9173-63b254973c68" />
