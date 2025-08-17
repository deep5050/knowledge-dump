
![04fig01](https://github.com/user-attachments/assets/2fdb9f4a-8a41-40ed-ab06-82b95f13cd46)

## 🛠️`sk_buff`

In the Linux kernel, particularly in the networking subsystem, **`sk_buff`** (socket buffer) is a crucial data structure used to manage network packets.
It serves as a container for network data and metadata, facilitating the handling of packets as they traverse through the networking stack.

## Where is sk_buff Used?

The sk_buff structure is extensively used throughout the Linux kernel's networking stack. Its primary purpose is to facilitate the management and processing of network packets as they move through various layers of the networking subsystem. Here are some key areas where sk_buff is utilized:
### 📜 Structure of `sk_buff`

The `sk_buff` structure contains various fields that store information about the packet, including its data, length, protocol, and other metadata. Here’s a simplified overview of its structure:

```c
struct sk_buff {
    struct sk_buff *next;        // Pointer to the next buffer in the list
    struct sk_buff *prev;        // Pointer to the previous buffer in the list
    struct net_device *dev;      // Pointer to the network device
    struct sock *sk;             // Pointer to the socket
    struct skb_shared_info *shinfo; // Shared information for the buffer
    unsigned char *data;         // Pointer to the start of the data
    unsigned char *tail;         // Pointer to the end of the data
    unsigned char *end;          // Pointer to the end of the buffer
    unsigned int len;            // Length of the data
    unsigned int data_len;       // Length of the data in the buffer
    unsigned int truesize;       // Actual size of the buffer
    // Additional fields...
};
```

### 🔍 Key Fields Explained

- **`next` and `prev`**: These pointers are used to link multiple `sk_buff` structures together, forming a list of packets.
- **`dev`**: This field points to the network device associated with the packet, allowing the kernel to know which interface to use for transmission.
- **`sk`**: This points to the socket associated with the packet, linking it to the user-space application.
- **`shinfo`**: This structure contains shared information about the buffer, such as reference counts and additional metadata.
- **`data`, `tail`, and `end`**: These pointers manage the actual data within the buffer, allowing for efficient data manipulation.
- **`len` and `data_len`**: These fields store the total length of the packet and the length of the data portion, respectively.
- **`truesize`**: This indicates the actual size of the memory allocated for the `sk_buff`, which may be larger than the data length due to overhead.

## Data Fields
Data Pointer: This points to the beginning of the data in the buffer. It allows the kernel to access the packet's payload.
Length: This indicates the total length of the data in the buffer.
Protocol: This field specifies the protocol used (e.g., IP, ARP) for the packet.
Transport Header: A pointer to the transport layer header (e.g., TCP, UDP) within the buffer.
Network Header: A pointer to the network layer header (e.g., IP) within the buffer.
Device Pointer: This points to the network device associated with the packet, helping in routing and processing.

## 📝 Sample Code Snippet to Handle `sk_buff`

Here's a simple example of how to create, manipulate, and free an `sk_buff` in a Linux kernel module. This snippet demonstrates how to allocate an `sk_buff`, fill it with data, and then free it after use.

### 📦 Code Example

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>

static int __init my_module_init(void) {
    struct sk_buff *skb;
    struct net_device *dev;
    unsigned char *data;
    int len = 100; // Length of the data to be sent

    // Allocate a new sk_buff
    skb = alloc_skb(len, GFP_KERNEL);
    if (!skb) {
        printk(KERN_ERR "Failed to allocate sk_buff\n");
        return -ENOMEM;
    }

    // Initialize the net_device (assuming you have a valid device)
    dev = dev_get_by_name(&init_net, "eth0"); // Replace "eth0" with your device name
    if (!dev) {
        printk(KERN_ERR "Failed to get net_device\n");
        kfree_skb(skb);
        return -ENODEV;
    }

    // Fill the sk_buff with data
    data = skb_put(skb, len); // Allocate space for data
    memset(data, 0, len); // Initialize data to zero (or fill with your data)

    // Set the protocol (e.g., ETH_P_IP for IPv4)
    skb->protocol = htons(ETH_P_IP);
    skb->dev = dev;

    // Optionally, you can set other fields like src/dst MAC addresses, etc.

    // Transmit the packet (this is just an example; actual transmission code may vary)
    dev_queue_xmit(skb);

    // Free the net_device reference
    dev_put(dev);

    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Module exiting\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Sample module to handle sk_buff");
```

### 🔍 Explanation of the Code

- **Module Initialization**: The `my_module_init` function is called when the module is loaded. It allocates an `sk_buff` and prepares it for transmission.
- **Allocating `sk_buff`**: The `alloc_skb` function is used to allocate memory for the `sk_buff`. The `GFP_KERNEL` flag indicates that the allocation is for kernel space.
- **Getting the Network Device**: The `dev_get_by_name` function retrieves a pointer to the specified network device (e.g., "eth0").
- **Filling the Buffer**: The `skb_put` function allocates space in the `sk_buff` for the data and returns a pointer to it. The data is then initialized.
- **Setting Protocol and Device**: The protocol is set using `htons` to convert the protocol number to network byte order, and the device is assigned to the `sk_buff`.
- **Transmitting the Packet**: The `dev_queue_xmit` function is called to transmit the packet. This function handles the actual sending of the packet through the network stack.
- **Cleanup**: The `dev_put` function releases the reference to the network device, and the module exit function is defined to clean up when the module is removed.

## Transmit Path Call Flow:

1. Application: write(socket, data, len)
2. TCP Layer: tcp_sendmsg() → adds TCP header 
3. IP Layer: ip_queue_xmit() → adds IP header
4. Routing: ip_finish_output() → determines output device
5. Ethernet Layer: eth_header() → adds Ethernet header
6. Device Layer: dev_queue_xmit() → calls driver  
7. NIC Driver: netdev->ndo_start_xmit() → maps complete packet to DMA
8. Hardware: DMA to NIC → transmit on wire

Key Files in Linux Kernel:
- net/ipv4/tcp_output.c (TCP header)  
- net/ipv4/ip_output.c (IP header)
- net/ethernet/eth.c (Ethernet header) ← CORRECTED LOCATION
- net/core/dev.c (device layer)
- drivers/net/ethernet/*/driver.c (DMA mapping only)

Receive Path:
- Driver receives frame from hardware
- skb->protocol = eth_type_trans(skb, dev); // Process existing header
- Pass to upper layers

## Key concepts

- Buffer Design: head ← [headroom] ← data ← [actual data] ← tail ← [tailroom] ← end
- Length Calculation: len = tail - data (NOT end - head)
- Efficiency: Headroom/tailroom enable zero-copy header operations
- Flexibility: Same buffer travels through entire network stack
- Performance: Eliminates costly memory allocations and copies
- Zero-copy operations: Headers can be added/removed without copying data (Fantastic idea!)
- <img width="1488" height="800" alt="1748229689334" src="https://github.com/user-attachments/assets/3a028ee3-8d78-46be-a5f9-58f7cd772951" />

  <img width="2074" height="861" alt="1748228856638" src="https://github.com/user-attachments/assets/273c4606-c601-4763-83e2-7c0a50f1f7a2" />

<img width="2066" height="720" alt="1748228881861" src="https://github.com/user-attachments/assets/8480a270-c1c0-4c12-b89e-d10d79244e73" />

### ⚠️ Note

This is a simplified example for educational purposes. In a real-world scenario, you would need to handle various aspects such as error checking, proper initialization of the network device, and possibly more complex packet handling logic.
