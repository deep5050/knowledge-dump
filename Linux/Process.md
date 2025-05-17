## Fork
In Linux, the `fork()` system call is used to create a new process by duplicating the calling process. The new process created is called the child process, and the process that calls `fork()` is referred to as the parent process. Here’s how `fork()` works in detail:

1. **Process Creation**: When a process calls `fork()`, the operating system creates a new process. This new process is an <mark style="background: #BBFABBA6;">almost exact duplicate </mark>of the parent process, including its memory space, file descriptors, and execution context.

2. **Return Values**: The `fork()` function returns a value that helps distinguish between the parent and child processes:
   - In the parent process, `fork()` returns the process ID (PID) of the child process.
   - In the <mark style="background: #BBFABBA6;">child process, `fork()` returns 0.</mark>

1. **Copy-on-Write**: Modern operating systems, including Linux, use a technique called "<mark style="background: #BBFABBA6;">copy-on-write</mark>" to optimize memory usage. Initially, <mark style="background: #BBFABBA6;">the parent and child processes share the same physical memory pages.</mark> Only <mark style="background: #BBFABBA6;">when one of the processes modifies a page does the operating system create a separate copy of that page for the modifying process.</mark> This approach minimizes the overhead of duplicating the entire memory space at the time of the `fork()` call.

2. **Process States**: After a successful `fork()`, both the parent and child processes will <mark style="background: #BBFABBA6;">execute the subsequent code independently</mark>. They can run concurrently, and their <mark style="background: #BBFABBA6;">execution order is not guaranteed.</mark>f After a fork(), it is indeterminate which process—the parent or the child—next has access to the CPU.

3. **Process IDs**: Each process in Linux has a unique process ID. The child process will have a different PID from the parent process, and the parent can use this PID to manage the child process (e.g., using `wait()` to wait for the child to finish).

4. **Example Usage**:
   Here’s a simple example of using `fork()` in a C program:

   ```c
   #include <stdio.h>
   #include <unistd.h>
   #include <sys/types.h>

   int main() {
       pid_t pid = fork();

       if (pid < 0) {
           // Error occurred
           perror("fork failed");
           return 1;
       } else if (pid == 0) {
           // Child process
           printf("I am the child process with PID: %d\n", getpid());
       } else {
           // Parent process
           printf("I am the parent process with PID: %d and my child's PID is: %d\n", getpid(), pid);
       }

       return 0;
   }
   ```

In this example, when you run the program, it will create a child process, and both the parent and child will print their respective PIDs.

1. **Process Termination**: After a child process has completed its task, it can terminate using the `exit()` system call. The <mark style="background: #BBFABBA6;">parent process can then use `wait()`</mark> or `waitpid()` to retrieve the child's exit status and clean up resources.
### Disadvantages

- <mark style="background: #FFB8EBA6;">It is difficult to share information between processes.</mark> Since the parent and child don’t share memory (other than the read-only text segment), we must use some form of inter process communication in order to exchange information between processes.
- Process creation with <mark style="background: #FFB8EBA6;">fork() is relatively expensive.</mark> Even with the copy-on-write technique the <mark style="background: #FFB8EBA6;">need to duplicate various process attributes such as page tables and file descriptor</mark> tables means that a fork() call is still time-consuming.


> spawn—that creates a new process that then executes a specified program.

### Orphan 

An orphan process is a process that continues to run after its parent process has terminated. <mark style="background: #BBFABBA6;">When a parent process exits before its child processes</mark>, those child processes become orphans.

- When a parent process terminates, the <mark style="background: #BBFABBA6;">orphaned child processes are adopted by the `init` process (process ID 1</mark>) in Unix-like systems.
- The <mark style="background: #BBFABBA6;">`init` process periodically calls `wait()`</mark> to clean up any terminated child processes, preventing them from becoming zombies.
- <mark style="background: #BBFABBA6;">Orphan processes can continue to run independently</mark> of their original parent process.
- <mark style="background: #FFF3A3A6;">Orphans are not problematic in the same way that zombie processes can be</mark>, as the `init` process takes responsibility for managing them.
### Zombie

A zombie process is <mark style="background: #BBFABBA6;">a process that has completed execution (terminated) but still has an entry in the process table</mark>. <mark style="background: #BBFABBA6;">child that terminates before its parent has had a chance to perform a wait()</mark>. This means that most of the resources held by the child are released back to the system to be reused by other processes. The only part of the process that remains is an entry in the kernel’s process table recording.

- <mark style="background: #BBFABBA6;">A zombie process can’t be killed by a signal, not even the SIGKILL</mark>. This ensures that the parent can always eventually perform a wait().
- When the parent does perform a wait(), the kernel removes the zombie, since the last remaining information about the child is no longer required. On the other hand, <mark style="background: #BBFABBA6;">if the parent terminates without doing a wait(), then the `nit` process adopts the child and automatically performs a wait(), thus removing the zombie process from the system.</mark>


## Exec

The <mark style="background: #BBFABBA6;">execve() system call loads a new program into a process’s memory.</mark> During this operation, the <mark style="background: #BBFABBA6;">old program is discarded</mark>, and the process’s stack, data, and heap are replaced by those of the new program.

The <mark style="background: #BBFABBA6;">most frequent use of execve() is in the child produced by a fork(),</mark> although it is also occasionally used in applications without a preceding fork().

The library functions described in this section provide alternative APIs for per forming an exec(). All of these functions are layered on top of execve(), and they dif fer from one another and from execve() only in the way in which the program name, argument list, and environment of the new program are specified.

```c
int execle(const char *pathname, const char *arg, ... /* , (char *) NULL, char *const envp[] */ );
int execlp(const char *filename, const char *arg, ... /* , (char *) NULL */); 
int execvp(const char *filename, char *const argv[]); 
int execv(const char *pathname, char *const argv[]); 
int execl(const char *pathname, const char *arg, ... /* , (char *) NULL */);
```

A sample code with arguments passed to new process:

```c
char *envVec[] = { "GREET=salut", "BYE=adieu", NULL };
char *filename;
execle(argv[1], filename, "hello world", (char *) NULL, envVec);
```

By default, <mark style="background: #BBFABBA6;">all file descriptors opened by a program that calls exec() remain open across the exec() and are available for use by the new program.</mark>

### system()

The system() function allows the calling program to execute an arbitrary shell command. In this section.

- We <mark style="background: #BBFABBA6;">don’t need to handle the details of calling fork(), exec(), wait(), and exit()</mark>
-  Because system() uses the shell to execute command, a<mark style="background: #BBFABBA6;">ll of the usual shell processing, substitutions, and redirections are performed on command before it is executed.</mark>
- Executing a command using <mark style="background: #FFB8EBA6;">system() requires the creation of at least two processes</mark>—<mark style="background: #FFB8EBA6;">one for the shell</mark> and o<mark style="background: #FFB8EBA6;">ne or more for the command(s) it executes</mark>—each of which performs an exec(). If efficiency or speed is a requirement, it is preferable to use explicit fork() and exec() calls to exe cute the desired program.
