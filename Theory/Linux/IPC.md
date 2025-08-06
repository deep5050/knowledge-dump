<img width="698" height="812" alt="image" src="https://github.com/user-attachments/assets/274ea16a-e6c6-480a-9aa9-7a9c0fed08df" />

Before we start:
- Byte stream: Each <mark style="background: #BBFABBA6;">read operation may read an arbitrary number of bytes</mark> from the IPC facility, regardless of the size of blocks written by the writer
- Message: Each read operation<mark style="background: #BBFABBA6;"> reads a whole message, as written by the writer process</mark>. It is <mark style="background: #FFB8EBA6;">not possible to read part of a message</mark>, leaving the remainder on the IPC facility; nor is it possible to read multiple messages in a single read operation.
## Unnamed Pipes

<img width="478" height="572" alt="image" src="https://github.com/user-attachments/assets/dd8fdee2-813d-485c-9862-b1885bc09be3" />


- **Creation:** `pipe()` system call creates two file descriptors (read and write ends) within the calling process.
- **Direction:** Unidirectional data flow <mark style="background: #BBFABBA6;">(write end → read end</mark>).
- **Processes:** Only for communication between **related processes** (typically parent and child after `fork()`).
- **Sharing:** File descriptors are inherited by child processes after `fork()`.
- **Naming:** No name in the file system; identified only by the file descriptors.
- **Kernel Buffer:** Data is buffered by the kernel. Writes block if full, reads block if empty (by default).
- **Closure:** Processes must close their respective ends after communication.

```c
pipe_fd[0]; // read
pipe_fd[1]; // write
READ SIDE: close(pipe_fd[1]); read(pipe_fd[0],buffer,size); close(pipe_fd[0]);
WRITE SIDE: close(pipe_fd[0]); write(pipe_fd[1], buffer, size); close(pipe_fd[1]);

```

## **Named Pipes (FIFOs):**

- **Creation:** `mkfifo()` system call or command creates a special file in the file system with a name (pathname).
- **Direction:** <mark style="background: #BBFABBA6;">Unidirectional data flow</mark> (one end for writing, one for reading).
- **Processes:** Allows communication between **unrelated processes**.
- **Access:** Processes open the named pipe using its pathname with standard file operations (`open()`).
- **Naming:** Has a persistent name in the file system.
- **Kernel Buffer:** Data is buffered by the kernel, with <mark style="background: #BBFABBA6;">blocking behavior on full writes or empty reads (by default).</mark>
- **Persistence:** The named pipe file persists even after processes close it; needs explicit deletion.

```c
#define PIPE_NAME "./MyPipe"
mknod(PIPE_NAME, S_IFIFO | 0660, 0); OR mkfifo(PIPE_NAME, 06661);
READ SIDE: fd = open(PIPE_NAME, O_RDONLY); read(fd, buffer, 128);
WRITE SIDE: open(PIPE_NAME, O_WRONLY); write(fd, buff, size);
```

## Shared Memory

-  The `shmget()` call returns a shared memory identifier (shmid), which acts like a handle to the segment.
-  Any process that knows the key and has the necessary permissions <mark style="background: #BBFABBA6;">can "attach" the segment to its own virtual address space</mark>. `shmat()` takes the shmid and returns a pointer to the starting address of the shared memory segment within the process's address space.
-   Multiple processes can attach to the same shared memory segment, and <mark style="background: #BBFABBA6;">it will appear at potentially different virtual addresses in each process.</mark>
-   Processes<mark style="background: #BBFABBA6;"> need to use synchronization mechanisms</mark> to coordinate their access to the shared memory. Semaphores, Mutex etc. is needed.
-  When a process no longer needs to access the shared memory segment, it should "detach" from it using a system call like `shmdt()`. Detaching does not destroy the shared memory segment; <mark style="background: #BBFABBA6;">it simply removes it from the process's address space</mark>. Other attached processes can still use it.
-  Eventually, the shared memory segment needs to be deallocated. This is typically done by the process that originally created it (or another process with appropriate permissions) using a system call like `shmctl()` with the `IPC_RMID` command (in POSIX systems)

### **Advantages of Shared Memory:**

- **Speed:** <mark style="background: #BBFABBA6;">Direct memory access is very fast</mark> compared to other IPC methods that involve copying data between processes (like pipes or message queues).  
- **Efficiency:** Less overhead as data doesn't need to be marshaled, copied, or un-marshaled.

### **Disadvantages of Shared Memory:**

- **Synchronization Complexity:** <mark style="background: #BBFABBA6;">Managing concurrent access</mark> and ensuring data consistency requires careful implementation of synchronization mechanisms, which can be complex and error-prone.  
- **Memory Management:** Processes need to agree on the structure and interpretation of the data in the shared memory segment.
- **Address Space Issues:** The shared memory segment might appear at different virtual addresses in different processes, requiring <mark style="background: #BBFABBA6;">careful use of pointers and offsets</mark>.

```c
#define KEY 123456
#define SEGMENT_SIZE 0xff // 256 bytes

CONTROLLING PROCESS:
	shared_id = shmget(KEY, SEGMENT_SIZE, IPC_CREAT | 0666);
	shmat(shared_id, NULL, 0); // own virtual address
	memcpy(shared_memory, buff, strlen(buff) + 1); // write something
	shmdt(shared_memory); // detach per process
	shmctl(shmid, IPC_RMID, NULL); // actual call to delete shm
OTHER PROCESS:
	shared_id = shmget(KEY, 0, 0); // get the already created address
	shmat(shmid, NULL, SHM_RDONLY); // Optional read-only
	shmdt(shared_memory); // Detach when done
```

## File based memory map

**Core Idea:** Instead of allocating a separate chunk of memory that exists only in RAM (like with anonymous mapping), file-backed mapping creates <mark style="background: #BBFABBA6;">a direct link between a portion of a file on disk and a region in a process's virtual address space.</mark>

- **Calling `mmap()`:** The process then calls `mmap()` with the following key parameters for file-backed mapping:- **`fd` (File Descriptor):** The file descriptor obtained from the `open()` call. This tells `mmap()` which file to associate with the memory mapping.  
	- **`offset`:** Specifies the starting offset within the file (in bytes) that should be mapped into memory. You can map the entire file (offset 0) or just a portion of it.
	- **`length`:** The size of the file region (in bytes) to be mapped.
	- **`prot` (Protection):** Specifies the access permissions for the mapped memory region (e.g., `PROT_READ`, `PROT_WRITE`, `PROT_READ | PROT_WRITE`, `PROT_EXEC`). These permissions must be compatible with the file's open mode.  
	- **`flags`:** Includes `MAP_SHARED` for inter-process communication (<mark style="background: #BBFABBA6;">changes are written back to the file and visible to other mappings</mark>) or `MAP_PRIVATE` (copy-on-write, changes are not shared or written back directly).
- **Mapping Creation:** The operating system then establishes a<mark style="background: #BBFABBA6;"> mapping between the specified portion of the file (from `offset` to `offset + length`) and a region in the calling process's virtual address space.</mark> The `mmap()` call returns a pointer to the starting address of this mapped region.
- **Accessing the File Contents via Memory:** The process can now access the content of the file by simply reading from or writing to the memory addresses within the mapped region. <mark style="background: #BBFABBA6;">The operating system handles the details of loading pages from the file into physical memory as needed</mark> (demand paging).


**Persistence:** The shared data is ultimately stored in a file on disk, providing a level of persistence that anonymous mappings lack. <mark style="background: #BBFABBA6;">The data can survive the termination of the processes using the mapping.</mark>

**Disk I/O:** <mark style="background: #BBFABBA6;">The initial access to mapped regions might involve disk I/O</mark> as the OS loads pages from the file into memory. Subsequent accesses to the same pages are typically faster as they reside in RAM.

**synchronization** mechanisms (like <mark style="background: #FF5582A6;">semaphores or file locks) are crucial</mark> when multiple processes with `MAP_SHARED` access the same file region concurrently to prevent data corruption.

Might need to use `msync()` to explicitly flush changes to disk.

Use cases:
- <mark style="background: #BBFABBA6;">Sharing configuration files</mark> or data files
-  **Sharing large datasets:** <mark style="background: #BBFABBA6;">Instead of loading an entire large file into memory, processes can map portions of it as needed.</mark>

```c
#define FILE_TO_MAP "./Map.txt"
#define MAPPING_SIZE 518

	struct flock lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
    lock.l_len = 0;
 WRITE PROCESS:
    lock.l_type = F_WRLCK;
    fd = open(FILE_TO_MAP, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    mapped = mmap( NULL, MAPPING_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	fcntl(fd, F_SETLKW, &lock);
	for(i = 0; i < MAPPING_SIZE; i++){
        mapped[i] = '*';
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    lock.l_type = F_RDLCK;
    fcntl(fd, F_SETLKW, &lock);
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    munmap(mapped, MAPPING_SIZE);
    close(fd); 
READ PROCESS:
    lock.l_whence = SEEK_SET;
	lock.l_start = 0;
    lock.l_len = 0;
	lock.l_type = F_RDLCK;
	fd = open(FILE_TO_MAP, O_RDWR);
	mapped = mmap( NULL, MAPPING_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	fcntl(fd, F_SETLKW, &lock);
	    for(i = 0; i < MAPPING_SIZE; i++){
        printf("%c", mapped[i]);
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    munmap(mapped, MAPPING_SIZE);
    close(fd);
```

## Anonymous Memory Map

- Used only in related processes
-   **synchronization mechanisms** are crucial to coordinate access and prevent race conditions if both processes are modifying the shared data concurrently.
-  Direct memory access is very fast.

```c
#define SHM_SIZE 256
PARENT PROCESS:
	mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // FD is null
	fork();
	strncpy(shared_memory, message, SHM_SIZE);
	wait(NULL);
CHILD PROCESS:
	printf("Child read: %s\n", shared_memory);
	munmap(shared_memory, SHM_SIZE);
```

Difference with unnamed pipes:

| Feature                | Unnamed Pipes            | Anonymous Memory Mapping           |
| ---------------------- | ------------------------ | ---------------------------------- |
| **Communication Type** | Unidirectional           | Bidirectional                      |
| **Data Format**        | Byte stream              | Structured data                    |
| **Blocking Behavior**  | Blocking reads/writes    | Non-blocking (unless synchronized) |
| **Lifetime**           | Tied to file descriptors | Tied to processes                  |
| **Use Case**           | Simple data transfer     | Sharing complex data structures    |
| **Creation**           | `pipe()`                 | `mmap()` with `MAP_ANONYMOUS`      |

## Socket

A powerful mechanism for communication between processes, <mark style="background: #BBFABBA6;">either on the same machine or across different machines over a network</mark>. There are several types of socket communication, each serving different purposes. Here are the main types:

Broadly there are two types of sockets: 
A. **Local sockets (AF_UNIX or AF_LOCAL)**
B. **Network sockets (AF_INET or AF_INET6)**

They can be further divided into

1. (Network) **Stream Sockets (TCP Sockets)**: <mark style="background: #BBFABBA6;">connection-oriented</mark> communication, data is delivered <mark style="background: #BBFABBA6;">in order and without duplication,</mark>  for applications that require <mark style="background: #BBFABBA6;">guaranteed delivery</mark>, such as web servers and database connections, Web applications, file transfers, <mark style="background: #BBFABBA6;">remote procedure calls</mark>.
2.  (Network) **Datagram Sockets (UDP Sockets)**: <mark style="background: #BBFABBA6;">connectionless</mark> communication,<mark style="background: #BBFABBA6;"> no guaranteed</mark> delivery, order, or error checking, <mark style="background: #BBFABBA6;">Streaming media,</mark> online gaming, voice over IP (VoIP).
3. (Local) **Unix Domain Sockets**: <mark style="background: #BBFABBA6;">same machine communication</mark>, SOCK_STREAM, SOCK_DGRAM, <mark style="background: #BBFABBA6;">faster than network sockets</mark> because they avoid the overhead of network protocols, <mark style="background: #BBFABBA6;">Local communication between processes</mark>, such as between a web server and a database server running on the same machine
4. (Network) **Raw Sockets**: <mark style="background: #BBFABBA6;">direct access to lower-layer protocols</mark>, <mark style="background: #BBFABBA6;">used for custom protocols</mark> or for network analysis, <mark style="background: #BBFABBA6;">requires administrative privileges</mark> to create, used in <mark style="background: #BBFABBA6;">network monitoring</mark>, custom protocol development.

Example of a stream communication:

```c
#define PORT 8080
#define BUFFER_SIZE 1024
SERVER:
	struct sockaddr_in address;
	int opt = 1;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	listen(server_fd, 3);
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen));
	read(new_socket, buffer, BUFFER_SIZE);
	close(new_socket);
CLIENT:
	sock = socket(AF_INET, SOCK_STREAM, 0));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	send(sock, message, strlen(message), 0);
	close(sock);
```

## POSIX Message Queue

- Allow processes to exchange messages in a structured and organized manner, supporting <mark style="background: #BBFABBA6;">both synchronous and asynchronous</mark> communication.
-  Messages can have a defined structure, typically consisting of <mark style="background: #BBFABBA6;">a priority and a data payload.</mark> The priority allows for prioritization of messages, enabling higher-priority messages to be processed before lower-priority ones.
-  Processes can send and receive messages<mark style="background: #BBFABBA6;"> without needing to be directly connected</mark>, allowing for decoupled communication.
- Messages are generally processed in a <mark style="background: #BBFABBA6;">First-In-First-Out (FIFO)</mark> order, a<mark style="background: #BBFABBA6;">lthough priority can affect</mark> the order in which messages are received.

There are two types of Message Queues:
1. Unnamed Queues: Generally used in related processes.
2. Named Queues: These are identified by a name (a string <mark style="background: #BBFABBA6;">starting with a `/`), allowing multiple processes to access the same queue.</mark>

```c
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
```

```c
#define QUEUE_NAME "/my_queue"
#define MESSAGE "Hello, POSIX Message Queue!"

SENDER_PROCESS:
	struct mq_attr attr;
	mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, NULL);
	mq_send(mq, MESSAGE, strlen(MESSAGE) + 1, 0);
	mq_close(mq);
	mq_unlink(QUEUE_NAME);

RECEIVER_PROCESS:
	mq = mq_open(QUEUE_NAME, O_RDONLY);
	unsigned int priority;
	ssize_t bytes_read = mq_receive(mq, buffer, BUFFER_SIZE, &priority);
	mq_close(mq);
```


## Semaphores



<hr>

### Conclusion:
1. Unnamed pipes: Suitable for simple data transfer between processes that have a common ancestor, such as a shell pipeline (e.g., `ls | grep "txt"`)
2. FIFO: Useful for communication between processes that do not share a common ancestor, such as a server and a client.
3. Message Queues: Ideal for task scheduling, <mark style="background: #BBFABBA6;">event notification</mark>, or when processes need to communicate without being directly connected.
4. Shared Memory: Best for <mark style="background: #BBFABBA6;">high-performance applications</mark> that require sharing large amounts of data, such as <mark style="background: #BBFABBA6;">multimedia processing or real-time data analysis</mark>.
5. Semaphores: Essential for preventing race conditions when multiple processes access shared resources, such as in producer-consumer scenarios.
6. TCP UDP Sockets: Communication endpoints that can be used for both local and network communication.
7. Unix Domain Sockets: Efficient for local IPC, such as communication between a web server and a database server running on the same host.

### Summary Table

|IPC Mechanism|Best Use Case|
|---|---|
|Unnamed Pipes|Simple data transfer between related processes|
|Named Pipes (FIFOs)|Communication between unrelated processes|
|Message Queues|Asynchronous communication and task scheduling|
|Shared Memory|High-performance data sharing|
|Semaphores|Synchronization for shared resource access|
|TCP Sockets|Reliable communication over networks|
|UDP Sockets|Fast, connectionless communication|
|Unix Domain Sockets|Efficient local IPC on the same machine|
