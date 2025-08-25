## CCSP PSM

PSM (Persistent Storage Manager) component is responsible for the storage of default/system configurations.

Provides software interfaces and abstractions to read/write variables stored in persistent storage and read factory config variables.

All defaults/system configuration which are not modified during runtime are part of PSM.

Configuration files are saved as below on the device:

-   /fss/gw/usr/ccsp/config/bbhm_def_cfg.xml !!
-   /nvram/bbhm_bak_cfg.xml
-   /nvram/bbhm_cur_cfg.xml

Factory reset removes the configuration files from nvram and copies default file to nvram.


Using CLI utility:  
psmcli get <parameter name as in bbhm file>  
Eg: psmcli get [eRT.com](http://ert.com/).cisco.spvtg.ccsp.Device.WiFi.NotifyWiFiChanges



## CCSP P-M


PandM is a CCSP component that implements core provisioning and management functionality of the device.  Its primary role is to respond to commands from other CCSP components and protocol agents that need to set or query variables pertaining to  provisioning and management. Its interface to other components uses the CCSP Message Bus interface and is based around a data model derived from  TR-181 (TR-157, TR-143) along with CCSP specific extensions. PandM is a Key module which holds parameters related to many key services like: dhcpv6, LAN, DeviceInfo etc. It maintains a TR181 data model XML file with dbus object path as /com/cisco/spvtg/ccsp/pam . Has a layered architecture which makes it less complex for GET/SET implementation.

P&M interfaces with Protocol Agent, Cr, PSM and other common components via the Message Bus Interface.Initialize On the lower side, P&M interfaces with the HAL layer modules, Ethernet, WiFi, MoCA, IP, DHCP client/server, etc.


##  CCSP WIFI AGENT

Wi-Fi component implements Wi-Fi functionality of the device, it supports all the parameters which are defined in the TR-181 data-model and CCSP specific Wi-Fi extensions.


Data-model Management Layer (DML) loads all data model access APIs through a pre-defined XML file TR181-Wi-Fi-USGV2.XML. An XML description of data model objects and parameters is given for Data Model Management Layer to load. Subsequently, Data Model Management Layer loads the shared library (libWi-Fi.so) which contains data model implementation, specified in the XML file.
The data model implementation in shared library interacts with HAL Integration Layer by calling component specific HAL APIs. These calls covert the user space calls to system level calls and takes the necessary action at driver level.


<img width="702" height="753" alt="Pasted image 20230516132654" src="https://github.com/user-attachments/assets/000c236b-e887-4661-aa23-5f01922c1eaf" />


## TR 181 & TR 069

TR-069 and TR-181 are two different specifications developed by the Broadband Forum, serving different purposes in the management of broadband devices. Here are the key differences between TR-069 and TR-181:

1. Purpose:
   - TR-069: <mark style="background: #FF5582A6;">TR-069 focuses on the protocol for remote management of customer premises equipment (CPE) by service providers. </mark>It enables service providers to remotely manage and configure CPE devices, perform firmware upgrades, monitor device status, and troubleshoot issues.
   - TR-181: TR-181 defines a standardized data model for managing broadband devices. It provides a hierarchical structure of objects and parameters that represent the various aspects of a device's configuration, status, and control.

2. Focus:
   - TR-069: The main focus of TR-069 is the communication between the CPE devices and the Auto Configuration Server (ACS) operated by the service provider. It specifies the protocol and message exchange format for managing CPE devices remotely.
   - TR-181: TR-181 primarily focuses on the data model representation of CPE devices. It defines the structure, attributes, and relationships of the parameters within the CPE, providing a standardized framework for managing and configuring these parameters.

3. Protocol vs. Data Model:
   - TR-069: TR-069 specifies the protocol used for communication between the ACS and CPE devices. It defines the HTTP-based CPE WAN Management Protocol (CWMP) for managing CPE devices remotely.
   - TR-181: TR-181 is a data model specification that defines the structure and organization of parameters within CPE devices. It provides a common and standardized representation of the data used for managing and configuring CPE devices.

4. Management vs. Data Representation:
   - TR-069: TR-069 enables service providers to remotely manage and configure CPE devices, perform diagnostics, and monitor device status. It focuses on the management aspects of CPE devices.
   - TR-181: TR-181 provides a standardized data model for representing the configuration, status, and control parameters of CPE devices. It focuses on the structure and representation of data within the CPE.

5. Usage Relationship:
   - TR-069 and TR-181 are related but serve different purposes:
      - TR-069 implementations commonly leverage the TR-181 data model for managing and configuring CPE devices. TR-181 provides a standardized framework for organizing the data managed through the TR-069 protocol.
      - TR-069 is concerned with the communication protocol and management operations, while TR-181 focuses on the structure and organization of data within the CPE.

In summary, TR-069 specifies the protocol for remote management of CPE devices, enabling service providers to manage and configure devices. TR-181 defines a standardized data model for representing the parameters and their relationships within CPE devices, facilitating consistent management and configuration across different devices.


## SBAPI

In the context of the RDKB CCSP stack, the "sbapi" directory refers to the directory that contains the implementation of the SBApi (Service Bus API). The SBApi is a component that provides a standardized interface for communication between different modules and components within the CCSP stack.

The SBApi facilitates inter-process communication and enables modules to exchange messages, notifications, and commands. It abstracts the details of the underlying communication mechanisms and provides a consistent and uniform interface for communication.

The SBApi directory typically contains the source code files and libraries related to the implementation of the SBApi. It may include files such as header files (.h), source code files (.c or .cpp), and any supporting files or libraries required for the proper functioning of the SBApi.

The SBApi plays a crucial role in the overall architecture of the CCSP stack by enabling seamless communication and interaction between different modules and components. It promotes modularity, code reuse, and interoperability within the stack.
