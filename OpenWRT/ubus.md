## **ubus** (micro bus) in OpenWrt

## 🛠️ Overview of ubus

### 📜 What is ubus?
**ubus** is a lightweight inter-process communication (IPC) system used in OpenWrt to facilitate communication between different processes and services. It allows various components of the system to interact with each other in a structured and efficient manner.

### 🏗️ Architecture
- **Client-Server Model**: ubus operates on a client-server model where clients can send requests to services (servers) and receive responses.
- **JSON-RPC Protocol**: Communication is typically done using the JSON-RPC protocol, which allows for easy serialization and deserialization of data.
- **Namespaces**: ubus organizes services into namespaces, allowing for better management and separation of different functionalities.

### 🔑 Key Components
- **ubus Daemon**: The central component that manages the communication between clients and services. It runs as a background process.
- **Services**: Various services register themselves with ubus, exposing methods that clients can call.
- **Clients**: Any application or script that wants to interact with ubus can act as a client, sending requests to the ubus daemon.

### 🛠️ ubus Commands
The `ubus` command-line tool is used to interact with the ubus system. Here are some common commands:

- **List Services**: Display all registered services.
  ```bash
  ubus list
  ```

- **Show Service Details**: Get detailed information about a specific service.
  ```bash
  ubus call <service> <method> <arguments>
  ```
  Example:
  ```bash
  ubus call network.interface.lan status
  ```

- **Subscribe to Events**: Listen for events published by services.
  ```bash
  ubus listen <event>
  ```

- **Call a Method**: Invoke a method on a registered service.
  ```bash
  ubus call <service> <method> <arguments>
  ```
  Example:
  ```bash
  ubus call system reboot
  ```

### 🔄 Practical Usage
1. **Network Management**: You can use ubus to query the status of network interfaces:
   ```bash
   ubus call network.interface.lan status
   ```

2. **System Control**: To reboot the system, you can call the reboot method:
   ```bash
   ubus call system reboot
   ```

3. **Event Subscription**: You can subscribe to events, such as changes in network status:
   ```bash
   ubus listen network.interface.lan
   ```

### 📚 Conclusion
**ubus** is a crucial component of the OpenWrt architecture, enabling efficient communication between various system components. Its lightweight design and use of JSON-RPC make it easy to integrate and use in scripts and applications. Understanding ubus is essential for developers and system administrators working with OpenWrt, as it provides a powerful way to manage and interact with the system. If you have any specific questions or need further details, feel free to ask!
