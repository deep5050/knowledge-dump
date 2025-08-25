##  Point-to-Point Protocol

Point-to-point connections are <mark style="background: #BBFABBA6;">typically used to connect two systems together over a wide area network (WAN</mark>). You can use a point-to-point connection to get data from your local system to a remote system or to get data from a local network to a remote network.

Point-to-Point Protocol (PPP) is one type of a point-to-point connection that is commonly used to connect a computer to the Internet.

<mark style="background: #FFF3A3A6;">It works on data link layer (2)</mark>

Since IP packets cannot be transmitted over a modem line on their own without some data link protocol that can identify where the transmitted frame starts and where it ends, <mark style="background: #FFF3A3A6;">Internet service providers (ISPs) have used PPP for customer dial-up access to the Internet.</mark>

<mark style="background: #FFF3A3A6;">Routers are point-to-point devices where PPP protocol is widely used as it is a WAN protocol not a simple LAN ethernet protocol.</mark>


Two derivatives of PPP, Point-to-Point Protocol over Ethernet (PPPoE) and Point-to-Point Protocol over ATM (PPPoA), are used most commonly by ISPs to establish a digital subscriber line (DSL) Internet service LP connection with customers.

PPP can provide services over multiple mediums, ranging from dial-up modems to Secure Sockets Layer (SSL)-encrypted virtual private network (VPN) connections. PPP uses a variation of High-level Data Link Control for packet encapsulation. For example, <mark style="background: #ABF7F7A6;">a high-security application on a company network connects to the network via the VPN and establishes an SSL link. The client for the application can then establish a PPP tunnel on top of that, which carries IP packets to the application's server.</mark>

<mark style="background: #ABF7F7A6;">PPP is also used to tunnel IP or other network Layer 3 data between two directly connected nodes over a physical connection or over a direct link</mark>. Since IP and TCP do not support point-to-point connections, the use of PPP can enable them over Ethernet and other physical media

## Services provided by the PPP protocol

- It <mark style="background: #FFF3A3A6;">defines the link establishment process</mark>. If user establishes a link with a server, then "how this link establishes" is done by the PPP protocol.
- It defines the authentication process between the two devices. <mark style="background: #FFF3A3A6;">The authentication between the two devices</mark>, handshaking and how the password will be exchanged between two devices are decided by the PPP protocol.

## Services Not provided by the PPP protocol

-   It does not support flow control mechanism.
-   It has a very simple error control mechanism.
-   As PPP provides point-to-point communication, so it <mark style="background: #FFB8EBA6;">lacks addressing mechanism to handle frames in multipoint configuration.</mark>

![[Pasted image 20221210195719.png]]




![[Pasted image 20221210195237.png]]



## PPPoE

The Point-to-Point Protocol over Ethernet (PPPoE) is a network protocol for encapsulating <mark style="background: #BBFABBA6;">Point-to-Point Protocol (PPP) frames inside Ethernet frames.</mark>

Typical use of <mark style="background: #BBFABBA6;">PPPoE involves leveraging the PPP facilities for authenticating the user with a username and password, predominately via the PAP</mark> or CHAP authentication protocols.

On the customer-premises equipment, PPPoE <mark style="background: #FFF3A3A6;">may be implemented either in a unified residential gateway device that handles both DSL modem and IP routing</mark> functions or in the case of a simple DSL modem (without routing support), <mark style="background: #FFF3A3A6;">PPPoE may be handled behind it on a separate Ethernet-only router or even directly on a user's computer</mark>.

### Use case

PPPoE is used mainly either:

1. with <mark style="background: #FFF3A3A6;">PPPoE-speaking Internet DSL services where a PPPoE-speaking modem-router (residential gateway) connects to the DSL service</mark>. Here both ISP and modem-router need to speak PPPoE. 

2. or when a <mark style="background: #BBFABBA6;">PPPoE-speaking DSL modem is connected to a PPPoE-speaking Ethernet-only router using an Ethernet cable</mark>.


<img width="1406" height="559" alt="Pasted image 20221210192000" src="https://github.com/user-attachments/assets/a5041090-28de-4828-989d-a38eb66033ab" />


<img width="1059" height="491" alt="Pasted image 20221210192121" src="https://github.com/user-attachments/assets/a0ec2b50-81c0-435a-bccf-89aa7e42f0c5" />


Competing WAN technologies (T1, ISDN) required a router on the customer premises. 
<mark style="background: #FFF3A3A6;">PPPoE used a different Ethernet frame type, which allowed the DSL hardware to function as simply a bridge, passing some frames to the WAN and ignoring the others</mark>. Implementation of such a bridge is multiple orders of magnitude simpler than a router.


## PPPoA
In computer networking, the Point-to-Point Protocol over ATM (PPPoA) is a layer 2 data-link protocol typically used to connect domestic broadband modems to ISPs <mark style="background: #FF5582A6;">via phone lines</mark>.

In the enterprise packages, PPPoA is typically the protocol of choice. It will require a Static IP configured straight into the hardware (modem). PPPoA is said to have less overheads compared to PPPoE therefore, the former is slightly faster than the latter. However, for the end-user, the difference in speed is almost negligible.


## Summary:

1. PPPoE means Point-to-Point Protocol over Ethernet while PPPoA means Point-to-Point Protocol over ATM.

2. PPPoE encapsulates PPP frames inside the Ethernet frames while<mark style="background: #FFF3A3A6;"> PPPoA encapsulates frames inside AAAL5.</mark>

3. PPPoE is often used in lower packages while PPPoA is often used in enterprise packages.

4. <mark style="background: #BBFABBA6;">PPPoE is more commonly used</mark> than PPPoA.

5. PPPoA has slightly less overhead than PPPoE therefore, it is a bit faster.

  ### ATM and AAL
  In Asynchronous Transfer Mode (ATM) networks, the ATM Adaptation Layer <mark style="background: #FFF3A3A6;">(AAL) provides facilities for non-ATM based networks to connect to ATM network and use its services</mark>.

AAL is basically a software layer that accepts user data, which may be digitized voice, video or computer data, and <mark style="background: #FFF3A3A6;">makes them suitable for transmission over an ATM network</mark>. The transmissions can be of fixed or variable data rate. AAL accepts higher layer packets and segments them into fixed sized ATM cells before transmission via ATM. It also reassembles the received segments to the higher layer packets.

```ad-tldr
**PPP**: Is used to connecte two systems encapsulating the layer 3. Can be used while getting internet access from ISPs (dial-ups), creating VPN etc.

**PPPoE**: Implements PPP over ethernet. Packets sent as ethernet frames at last.

**PPPoA**: Implemetns PPP over ATM. Used to transmit data over telephone lines. Needs convert mechanism (AAL5) It is not widely used as of PPPoE.

```

## Sources

1. https://www.javatpoint.com/ppp-protocol
2. https://en.wikipedia.org/wiki/Point-to-Point_Protocol_over_Ethernet
3. [[PPP.excalidraw]]
4. [[adsl.excalidraw]]
5. [[PPPoE.excalidraw]]
