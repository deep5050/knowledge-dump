## 🌐 Overview of Remote Procedure Calls (RPC)

Remote Procedure Call (RPC) is a powerful communication protocol that allows a program to execute a procedure (subroutine) on a different address space, typically on a remote server. This mechanism abstracts the complexities of network communication, making it appear as if the procedure is being called locally.

### Key Features

- **Abstraction**: RPC hides the details of the network communication, allowing developers to call remote services as if they were local functions.
- **Client-Server Model**: In an RPC setup, the client sends a request to the server, which processes the request and sends back a response.
- **Data Serialization**: Data sent over the network must be serialized (converted into a format suitable for transmission) and deserialized on the receiving end.

### Advantages

- **Simplicity**: Developers can focus on the application logic without worrying about the underlying network protocols.
- **Interoperability**: RPC can facilitate communication between different systems and programming languages, provided they adhere to the same RPC protocol.
- **Modularity**: It promotes a modular architecture, allowing different components of an application to be developed and maintained independently.

### Disadvantages

- **Network Latency**: RPC calls can be slower than local calls due to network delays.
- **Error Handling**: Handling network errors and timeouts can complicate the implementation.
- **Complexity in Debugging**: Debugging remote calls can be more challenging than local calls due to the distributed nature of the system.


## 🛠️ Implementing Remote Procedure Call (RPC) in C

To implement RPC in C, you can use the RPC library provided by the operating system, such as the Sun RPC (also known as ONC RPC). Below is a step-by-step guide to creating a simple RPC application in C.

### 1. **Define the RPC Service**

Create a file named `example.x` to define the RPC service and the procedures.

```c
/* example.x */
program EXAMPLE_PROG {
    version EXAMPLE_VERS {
        string SAY_HELLO(string) = 1;
    } = 1;
} = 0x20000001;
```

### 2. **Generate the RPC Code**

Use the `rpcgen` tool to generate the necessary C code from the `.x` file.

```bash
rpcgen example.x
```

This command will generate several files:
- `example.h`: Header file with definitions.
- `example_clnt.c`: Client-side stubs.
- `example_svc.c`: Server-side stubs.
- `example_xdr.c`: XDR (External Data Representation) routines.

### 3. **Implement the Server**

Edit the `example_svc.c` file to implement the server logic.

```c
// example_svc.c
#include <stdio.h>
#include <stdlib.h>
#include "example.h"

char **say_hello_svc(char **name, struct svc_req *req) {
    static char *response;
    response = malloc(100);
    snprintf(response, 100, "Hello, %s!", *name);
    return &response;
}

int main() {
    pmap_unset(EXAMPLE_PROG, EXAMPLE_VERS);
    register SVCXPRT *transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL) {
        fprintf(stderr, "Error: Unable to create UDP service.\n");
        exit(1);
    }
    if (!svc_register(transp, EXAMPLE_PROG, EXAMPLE_VERS, svcudp_bufcreate, IPPROTO_UDP)) {
        fprintf(stderr, "Error: Unable to register service.\n");
        exit(1);
    }
    svc_run();
    fprintf(stderr, "Error: svc_run returned.\n");
    exit(1);
}
```

### 4. **Implement the Client**

Edit the `example_clnt.c` file to implement the client logic.

```c
// example_clnt.c
#include <stdio.h>
#include <stdlib.h>
#include "example.h"

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    char *server;
    char *name;
    char **result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server> <name>\n", argv[0]);
        exit(1);
    }
    server = argv[1];
    name = argv[2];

    clnt = clnt_create(server, EXAMPLE_PROG, EXAMPLE_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(server);
        exit(1);
    }

    result = say_hello_1(&name, clnt);
    if (result == NULL) {
        clnt_perror(clnt, server);
        exit(1);
    }
    printf("Response from server: %s\n", *result);
    clnt_destroy(clnt);
    return 0;
}
```

### 5. **Compile the Code**

Compile the generated and implemented files.

```bash
gcc -o server example_svc.c example_xdr.c -lnsl
gcc -o client example_clnt.c example_xdr.c -lnsl
```

### 6. **Run the Server and Client**

1. Start the server:
   ```bash
   ./server
   ```

2. In another terminal, run the client:
   ```bash
   ./client localhost "World"
   ```

### Summary

This example demonstrates a basic RPC implementation in C using Sun RPC. The steps include defining the service, generating the necessary code with `rpcgen`, and implementing both the server and client. This approach allows for communication between processes on the same machine or over a network.
