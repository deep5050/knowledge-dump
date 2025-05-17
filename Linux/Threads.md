Threads are the smallest unit of processing that can be scheduled by an operating system. They are a way to achieve concurrent execution within a program, allowing multiple

A thread is a lightweight process that <mark style="background: #BBFABBA6;">shares the same memory space and resources of its parent process.</mark> Multiple threads within the same process can communicate with each other more easily than separate processes because they share the same memory.

Thread creation is faster typically 10X because many of the attributes that must be duplicated in a child created by fork() are instead shared between threads. i.e. <mark style="background: #BBFABBA6;">memory and other attribute duplication is not needed.
</mark>

These are some of the things that is shared between threads: Process Id, group Id, <mark style="background: #FFF3A3A6;">open file descriptors</mark>, <mark style="background: #FFF3A3A6;">umasks</mark>, current working directory, signal masks, <mark style="background: #FFF3A3A6;">errno</mark>
1. **Thread States**: Threads can be in various states during their lifecycle:
    - **New**: The thread is created but not yet started.
    - **Runnable**: The thread is ready to run and is waiting for CPU time.
    - **Blocked**: The thread is waiting for a resource (like I/O) to become available.
    - **Terminated**: The thread has completed its execution.
- **Benefits of Using Threads**:
    - **Concurrency**: <mark style="background: #FFF3A3A6;">Threads allow for concurrent execution</mark>, which can lead to better resource utilization and improved application performance.
    - **Responsiveness**: In user interface applications, using threads can keep the interface responsive while performing background tasks.
    - **Resource Sharing**: Threads share the same memory space, which makes it easier to share data between them compared to inter-process communication (IPC) methods used between processes.

The main difference is:
- <mark style="background: #FFB8EBA6;">Each process has its own separate memory space,</mark> including code, data, and stack segments.
- <mark style="background: #BBFABBA6;">Threads within the same process share the same memory space</mark> and resources (such as file descriptors).
-  <mark style="background: #FFB8EBA6;">Inter-process communication (IPC) mechanisms (such as pipes, message queues, shared memory, and sockets) are required for processes</mark> to communicate with each other, which can be more complex and slower due to the isolation of memory spaces. 
- <mark style="background: #BBFABBA6;">Threads can communicate with each other more easily</mark> since they share the same memory space. They can directly read and write to shared variables, but this requires synchronization mechanisms (like mutexes and semaphores) to prevent data corruption.
- Processes have higher overhead due to their separate memory spaces and the <mark style="background: #FFB8EBA6;">need for context switching between processes,</mark> which is <mark style="background: #FFB8EBA6;">more resource-intensive.</mark>
-  Threads have lower overhead because they share the same memory space and resources, making context switching between threads <mark style="background: #BBFABBA6;">faster and less resource-intensive</mark>.

```c
#include <pthread.h>
void* thread_function(void* arg) { 
	// do some work
	return NULL;
}

int main()
{
	pthread_t thread;
	pthread_create(&thread, NULL, thread_function, NULL);
	pthread_join(thread, NULL);
}
```

```bash
gcc -o thread single_thread_example.c -pthread
```

- Threads are peers. Any thread in a process can use pthread_join() to join with any other thread in the process.

## Synchronization Techniques

Threads can use to synchronize their actions: mutexes and condition variables. <mark style="background: #FFF3A3A6;">Mutexes allow threads to synchronize their use of a shared resource</mark>, so that, for example, one thread doesn’t try to access a shared variable at the same time as another thread is modifying it. <mark style="background: #FFF3A3A6;">Condition variables  allow threads to inform each other that a shared variable (or other shared resource) has changed state</mark>.

### Mutex

- The term <mark style="background: #BBFABBA6;">critical section is used to refer to a section of code that accesses a shared resource and whose execution should be atomic;</mark> that is, its execution should not be interrupted by another thread that simultaneously accesses the same shared resource.
- mutex (short for mutual exclusion) to <mark style="background: #BBFABBA6;">ensure that only one thread at a time can access the variable</mark>. More generally, mutexes can be used to ensure atomic access to any shared resource, but protecting shared variables is the most common use.
-  A mutex has two states: locked and unlocked. At any moment,<mark style="background: #BBFABBA6;"> at most one thread may hold the lock on a mutex.</mark> When a thread locks a mutex, it becomes the owner of that mutex. <mark style="background: #BBFABBA6;">Only the mutex owner can unlock the mutex.</mark>
-  A mutex can either be allocated as a static variable or be created dynamically at run time.
	- Static: `pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER`
	- Dynamic: `int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);` The mutex was dynamically allocated on the heap.
-  If the mutex is currently locked by another thread, then <mark style="background: #BBFABBA6;">pthread_mutex_lock() blocks until the mutex is unlocked,</mark> at which point it locks the mutex and returns.
-  <mark style="background: #FFF3A3A6;">If the calling thread itself has already locked the mutex </mark>given to `pthread_mutex_lock()`, then, for the default type of mutex, one of two implementation defined possibilities may result: the thread deadlocks, blocked trying to lock a mutex that it already owns, or the call fails, returning the error EDEADLK. <mark style="background: #FFF3A3A6;">On Linux, the thread deadlocks by default.</mark>
-  <mark style="background: #FFF3A3A6;">It is an error to unlock a mutex that is not currently locked</mark>, or to unlock a mutex that is locked by another thread.
- The `pthread_mutex_trylock()` function is the same as `pthread_mutex_lock()`, except that if the mutex is currently locked, `pthread_mutex_trylock()` fails, returning the error EBUSY.
-  When <mark style="background: #FFB8EBA6;">more than one thread is locking the same set of mutexes, deadlock situations can arise.</mark>
- ![Pasted image 20250513123948](https://github.com/user-attachments/assets/1f7ee137-3cd0-434f-9d20-5e94184f2308)

-  <mark style="background: #BBFABBA6;">When threads can lock the same set of mutexes, they should always lock them in the same order.</mark>
-  To avoid deadlock an alternative strategy that is less frequently used is “try, and then back off.” In this strategy, a thread locks the first mutex using `pthread_mutex_lock()`, and then locks the remaining mutexes using` pthread_mutex_trylock()`. If any of the `pthread_mutex_trylock()` calls fails (with EBUSY), then the thread releases all mutexes, and then tries again, perhaps after a delay interval

Example of Mutex:

```c
#include <pthread.h>
int global_var = 0;
pthread_mutex_t global_var_mutex;

void* thread_function(void* arg) { 
	pthread_mutex_lock(&global_var_mutex); //lock
	global_var++;
	pthread_mutex_unlock(&global_var_mutex); //unlock
	return NULL;
}

int main()
{
	pthread_t thread[2];
	pthread_mutex_init(&counter_mutex, NULL); // init mutex
	pthread_create(&thread[0], NULL, thread_function, NULL);
	pthread_create(&thread[1], NULL, thread_function, NULL);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_mutex_destroy(&global_var_mutex); // destroy mutex
}
```

A deadlock situation:

```c
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* thread1_function(void* arg){
	pthread_mutex_lock(&mutex1);
	sleep(1);
	pthread_mutex_lock(&mutex2);
	
	pthread_mutex_unlock(&mutex2); 
	pthread_mutex_unlock(&mutex1);
	return NULL;
}
void* thread2_function(void* arg) {
	pthread_mutex_lock(&mutex2); // !! should not lock mutex2 before mutex1
	sleep(1);
	pthread_mutex_lock(&mutex1);

	pthread_mutex_unlock(&mutex1);
	pthread_mutex_unlock(&mutex2);
	return NULL;
}

int main()
{
	pthread_t thread1, thread2;
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);

	pthread_create(&thread1, NULL, thread1_function, NULL);
	pthread_create(&thread2, NULL, thread2_function, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	
}
```

Deadlock avoid best practices:

 - Always<mark style="background: #BBFABBA6;"> acquire locks in a consistent order across all threads</mark>.
 -  Use `pthread_mutex_trylock(&mutex)`, This function <mark style="background: #FFF3A3A6;">attempts to lock the mutex without blocking.</mark> If the mutex is already locked, it returns immediately with an error code, allowing the thread to take alternative actions (like backing off or trying again later).
 -  Use timeouts when trying to acquire locks, allowing threads to back off and retry. 
```c
struct timespec ts;
clock_gettime(CLOCK_REALTIME, &ts);
ts.tv_sec += 1; // Wait for 1 second 
if (pthread_mutex_timedlock(&mutex, &ts) != 0) { 
	// Handle the timeout situation 
}
```
 -  <mark style="background: #FFF3A3A6;">Condition variables can be used in conjunction with mutexes to manage resource availability more effectively</mark>. Instead of blocking on a mutex, a thread can wait on a condition variable, which allows other threads to signal when resources are available. `pthread_cond_wait(&cond_var, &mutex);`
 -  If your application has a scenario where multiple threads need to read shared data but only one thread needs to write, consider using read-write locks (`pthread_rwlock_t`). <mark style="background: #FFF3A3A6;">This allows multiple readers to access the resource simultaneously while ensuring exclusive access for writers.</mark>


## Condition variables

- Useful for coordinating the actions of multiple threads that share resources or need to communicate about the state of those resources. They h<mark style="background: #BBFABBA6;">elp avoid busy-waiting, where a thread continuously checks a condition in a loop,</mark> consuming CPU resources unnecessarily.
-  Condition variables <mark style="background: #BBFABBA6;">are typically used in conjunction with mutexes</mark> (or other locking mechanisms) to protect shared data. A thread will lock a mutex, check a condition, and if the condition is not met, it will wait on the condition variable. When another thread changes the state of the shared data, it can signal the condition variable to wake up waiting threads.
-  **`pthread_cond_wait()`**: This function is used by a thread to wait for a condition variable. <mark style="background: #BBFABBA6;">It atomically releases the associated mutex and puts the thread to sleep until the condition variable is signaled.</mark>
- **`pthread_cond_signal()`**: This function <mark style="background: #BBFABBA6;">wakes up one of the threads that are waiting on the condition variable.</mark>
- **`pthread_cond_broadcast()`**: This function w<mark style="background: #BBFABBA6;">akes up all threads</mark> that are waiting on the condition variable.

```c
#include <pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond_full; 
pthread_cond_t cond_empty;
int buffer[BUFFER_SIZE];
int count = 0;

void* producer(void* arg) {
	for (int i = 0 ; i < 10; i++)
	{
		pthread_mutex_lock(&mutex);
		while (count == BUFFER_SIZE) {
			pthread_cond_wait(&cond_full, &mutex);
		}
		buffer[count] = i;
		printf("Produced: %d\n", buffer[count]);
		count++;
		pthread_cond_signal(&cond_empty);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	return NULL;
}
void* consumer(void* arg) {
	for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mutex);
		while (count == 0) {
			pthread_cond_wait(&cond_empty, &mutex);
		}
		int item = buffer[count - 1];
		count--;
		printf("Consumed: %d\n", item);
		pthread_cond_signal(&cond_full);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t prod_thread, cons_thread;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_full, NULL);
	pthread_cond_init(&cond_empty, NULL);
	pthread_create(&prod_thread, NULL, producer, NULL);
	pthread_create(&cons_thread, NULL, consumer, NULL);
	pthread_join(prod_thread, NULL);
	pthread_join(cons_thread, NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_full);
	pthread_cond_destroy(&cond_empty);
	return 0;
}
```
