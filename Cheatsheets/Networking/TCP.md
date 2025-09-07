<img width="6000" height="3375" alt="image" src="https://github.com/user-attachments/assets/1ef92690-5a80-4a02-be3d-658b421642ab" />

<img width="840" height="564" alt="image" src="https://github.com/user-attachments/assets/9b46ccf4-c3ec-4aa9-9a10-561063cd97cd" />


## Overview of TCP Protocol

The **Transmission Control Protocol (TCP)** is one of the core protocols of the Internet Protocol Suite. It is primarily responsible for ensuring reliable, ordered, and error-checked delivery of data between applications running on hosts communicating over an IP network. TCP is widely used for applications where data integrity and order are critical, such as web browsing, email, and file transfers.

---

## Key Features of TCP

### 1. **Connection-Oriented Protocol**
TCP establishes a connection between the sender and receiver before data transmission begins. This is done through a process known as the **three-way handshake**.

### 2. **Reliable Data Transfer**
TCP ensures that data is delivered accurately and in the correct order. It uses acknowledgments (ACKs) to confirm receipt of packets and retransmits any lost packets.

### 3. **Flow Control**
TCP implements flow control using a mechanism called **windowing**. This allows the sender to send a certain amount of data before needing an acknowledgment, preventing overwhelming the receiver.

### 4. **Congestion Control**
TCP includes algorithms to manage network congestion, adjusting the rate of data transmission based on network conditions. This helps to prevent packet loss and ensures efficient use of network resources.

### 5. **Error Detection and Correction**
TCP uses checksums to detect errors in transmitted segments. If an error is detected, the affected segment is retransmitted.

---

## TCP Header Structure

The TCP header is crucial for the protocol's functionality. It contains several fields that help manage the connection and data transfer. Here’s a breakdown of the TCP header structure:

| Field Name         | Size (bits) | Description                                                                 |
|--------------------|-------------|-----------------------------------------------------------------------------|
| Source Port        | 16          | The port number of the sender.                                             |
| Destination Port   | 16          | The port number of the receiver.                                           |
| Sequence Number     | 32          | The sequence number of the first byte of data in this segment.            |
| Acknowledgment Number | 32        | The sequence number of the next byte expected from the sender.            |
| Data Offset        | 4           | The size of the TCP header in 32-bit words.                               |
| Reserved           | 3           | Reserved for future use, must be set to zero.                             |
| Flags              | 9           | Control flags (e.g., SYN, ACK, FIN, RST, PSH, URG).                      |
| Window Size        | 16          | The size of the sender's receive window (flow control).                   |
| Checksum           | 16          | A checksum for error-checking the header and data.                        |
| Urgent Pointer     | 16          | Indicates if there is urgent data in the segment.                         |
| Options            | Variable     | Optional fields for various features (e.g., Maximum Segment Size).       |
| Data               | Variable     | The actual data being transmitted.                                        |

---

## TCP Connection Establishment: The Three-Way Handshake

1. **SYN**: The client sends a SYN (synchronize) packet to the server to initiate a connection.
2. **SYN-ACK**: The server responds with a SYN-ACK (synchronize-acknowledge) packet, acknowledging the client's request and sending its own SYN.
3. **ACK**: The client sends an ACK (acknowledge) packet back to the server, completing the connection establishment.

---

## TCP Connection Termination

TCP connections are terminated using a four-way handshake:

1. **FIN**: One side sends a FIN (finish) packet to indicate it wants to close the connection.
2. **ACK**: The other side acknowledges the FIN with an ACK.
3. **FIN**: The second side then sends its own FIN to close the connection.
4. **ACK**: The first side acknowledges this FIN with an ACK.

---

## Applications of TCP

TCP is used in various applications, including:

- **Web Browsing**: HTTP and HTTPS protocols rely on TCP for reliable data transfer.
- **Email**: Protocols like SMTP, POP3, and IMAP use TCP to ensure emails are sent and received correctly.
- **File Transfer**: FTP and SFTP protocols utilize TCP for reliable file transfers.

---

TCP is a fundamental protocol that plays a critical role in ensuring reliable communication over the internet. Its features, such as connection-oriented communication, error detection, and flow control, make it suitable for a wide range of applications where data integrity is paramount.
