The Ethernet header is a crucial part of the Ethernet frame, which is used in networking to encapsulate data for transmission over a local area network (LAN). The structure of an Ethernet header is defined by the IEEE 802.3 standard and typically consists of several fields that provide essential information about the frame.


<img width="1024" height="769" alt="Ethernet-Frame-Header-Types-ipcisco-1024x769-1501287708" src="https://github.com/user-attachments/assets/0edab105-53a7-4913-a6aa-90db820b87e2" />


## Structure of an Ethernet Header

The Ethernet header is 14 bytes long and consists of the following fields:

| Field Name          | Size (Bytes) | Description                                                                 |
|---------------------|--------------|-----------------------------------------------------------------------------|
| `preamble`          | 8            | It serves as a synchronization mechanism that helps devices on a network identify the beginning of a frame and prepare for the incoming data |
| `Destination MAC`   | 6            | The MAC address of the destination device.                                  |
| `Source MAC`        | 6            | The MAC address of the source device (the sender).                         |
| `EtherType/Length`  | 2            | Indicates the type of the payload (EtherType) or the length of the payload in some cases. |
| `Payload`           | 46-1500      | The actual data being transmitted, which can vary in size.                |
| `Frame Check Sequence (FCS)` | 4 | A 32-bit cyclic redundancy check (CRC) used for error-checking.           |

### Detailed Breakdown of Each Field

### Structure of the Preamble
- Length: The preamble is typically 7 bytes (56 bits) long.

- Content: It consists of alternating 1s and 0s, specifically the pattern 10101010 repeated seven times, followed by a Start Frame Delimiter (SFD), which is a single byte with the value **10101011**.
The preamble consists of a series of bits that precede the actual Ethernet frame. Here are the key details:

### Purpose of the Preamble

- Synchronization: The primary purpose of the preamble is to allow the receiving device to **synchronize its clock with the incoming signal**. This ensures that the receiver can accurately interpret the bits of the frame.
- Frame Detection: The preamble helps devices recognize the start of a new frame. **The SFD indicates that the actual frame data is about to begin.**
- Collision Detection: In older Ethernet standards that used Carrier Sense Multiple Access with Collision Detection (CSMA/CD), the preamble also played a role in helping devices detect collisions on the network.
### 1. Destination MAC Address
- **Size**: 6 bytes
- **Description**: This field contains the MAC address of the device that is intended to receive the frame. It is used to ensure that the frame is delivered to the correct destination.

### 2. Source MAC Address
- **Size**: 6 bytes
- **Description**: This field contains the MAC address of the device that is sending the frame. It allows the recipient to know where the frame originated.

### 3. EtherType/Length
- **Size**: 2 bytes
- **Description**: This field can serve two purposes:
  - **EtherType**: If the value is greater than 1500, it indicates the type of protocol encapsulated in the payload (e.g., IPv4, IPv6, ARP).
  - **Length**: **If the value is less than or equal to 1500, it indicates the length of the payload in bytes.
**
### 4. Payload
- **Size**: 46 to 1500 bytes
- **Description**: This field contains the actual data being transmitted. The minimum size of the payload must be 46 bytes to ensure that the entire frame is at least 64 bytes long (including the header and FCS).** If the payload is less than 46 bytes, padding is added.
**
### 5. Frame Check Sequence (FCS)
- **Size**: 4 bytes
- **Description**: This field contains a 32-bit CRC value that is used for error-checking. The sender calculates the CRC based on the contents of the frame, and the receiver checks this value to detect any errors that may have occurred during transmission.

### Example of Ethernet Header Structure in C

Here’s a simple representation of the Ethernet header structure in C:

```c
#include <stdint.h>

struct ethernet_header {
    uint8_t destination_mac[6]; // Destination MAC address
    uint8_t source_mac[6];      // Source MAC address
    uint16_t ether_type;        // EtherType or Length
};
```

### Conclusion

The Ethernet header is essential for the proper functioning of Ethernet networks, providing the necessary information for data transmission and ensuring that frames are delivered to the correct destinations. Understanding its structure is crucial for anyone working with network protocols and data communication.
