## Socket Programming in Linux

**Socket programming** in Linux is a way to enable communication between different processes, either on the same machine or across a network. It provides a standardized interface for network communication, allowing developers to create applications that can send and receive data over various protocols.

<hr>

### Key Concepts

#### Sockets

- **Definition**: A socket is an endpoint for sending or receiving data across a network. It is defined by an IP address and a port number.
- **Types**: The two main types of sockets are:
  - **Stream Sockets (TCP)**: Provide reliable, connection-oriented communication.
  - **Datagram Sockets (UDP)**: Provide connectionless communication, which is faster but less reliable.

#### Socket API

- **System Calls**: Socket programming in Linux involves several system calls, including:
  - **socket()**: Creates a new socket.
  - **bind()**: Associates a socket with a specific IP address and port.
  - **listen()**: Prepares a socket to accept incoming connections (for TCP).
  - **accept()**: Accepts a connection request from a client (for TCP).
  - **connect()**: Establishes a connection to a server (for TCP).
  - **send()** and **recv()**: Used to send and receive data.
  - **close()**: Closes the socket.

### Steps in Socket Programming

1. **Create a Socket**: Use the `socket()` function to create a socket.
2. **Bind the Socket**: Use the `bind()` function to bind the socket to an IP address and port.
3. **Listen for Connections**: For server applications, use `listen()` to wait for incoming connections.
4. **Accept Connections**: Use `accept()` to accept a connection from a client.
5. **Data Transmission**: Use `send()` and `recv()` to exchange data between the client and server.
6. **Close the Socket**: Use `close()` to release the resources associated with the socket.

### Example Code

Here’s a simple example of a TCP server in C:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    // Accept a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
    }

    // Read data
    read(new_socket, buffer, 1024);
    printf("Message from client: %s\n", buffer);

    // Close the socket
    close(new_socket);
    close(server_fd);
    return 0;
}
```

### Applications

- **Web Servers**: Handle HTTP requests and responses.
- **Chat Applications**: Enable real-time communication between users.
- **File Transfer**: Allow users to send and receive files over a network.
- **IoT Devices**: Facilitate communication between devices in an Internet of Things environment.

Socket programming in Linux is a fundamental skill for developers working on networked applications, providing the tools necessary to create robust and efficient communication systems.
