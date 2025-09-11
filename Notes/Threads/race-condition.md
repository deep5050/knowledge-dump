# **1. Critical Sections & Race Conditions**

### **Critical Section**

* A **critical section** is a block of code that **accesses shared resources** (memory, files, sockets, hardware, etc.) that must not be accessed by more than one thread at a time.
* Example: Updating a shared counter, writing to a file, or modifying a global linked list.

👉 Problem: If multiple threads enter the critical section simultaneously, you may end up with **inconsistent or corrupted state**.

---

# **2. What is a Race Condition?**

A **race condition** occurs when:

* The **correctness of a program depends on the timing or interleaving of threads**,
* And **two or more threads access shared data concurrently**,
* At least one of them **writes** to that data.

⚠️ Key idea: If the outcome of your program changes depending on how the OS schedules threads → you have a race condition.

---

# **3. Why Synchronization is Needed**

* Modern CPUs run **multiple threads in parallel** (on multiple cores).
* Even on a single-core CPU, the scheduler can **preempt** one thread and run another between instructions.
* Without synchronization, two threads can **interleave their instructions in unpredictable ways**, causing:

  * Wrong results
  * Data corruption
  * Hard-to-reproduce bugs

👉 Synchronization primitives (mutex, semaphore, etc.) are used to **serialize access** so only one thread changes shared state at a time.

---

# **4. Example: Incrementing a Global Counter**

Suppose you have:

```c
int counter = 0;

void* worker(void* arg) {
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
    return NULL;
}
```

And you run two threads:

```c
pthread_t t1, t2;
pthread_create(&t1, NULL, worker, NULL);
pthread_create(&t2, NULL, worker, NULL);
pthread_join(t1, NULL);
pthread_join(t2, NULL);

printf("Counter = %d\n", counter);
```

### **What you expect:**

`Counter = 200000`

### **What you often get:**

Something like `Counter = 173456` or `189230` (non-deterministic).

---

### **Why does this happen?**

`counter++` looks like a single operation, but it’s actually 3 machine instructions:

1. Load counter into register
2. Increment register
3. Store register back to memory

If two threads interleave:

```
Thread A: Load counter (100)
Thread B: Load counter (100)
Thread A: Increment → 101
Thread B: Increment → 101
Thread A: Store 101
Thread B: Store 101
```

Expected result = 102, but actual = 101 → **lost update**.

This is the essence of a **race condition**.

---

✅ **Takeaway so far:**

* Critical section = code that must not be executed by multiple threads at once.
* Race condition = occurs when two threads access the same shared resource concurrently without synchronization, causing incorrect results.
* Synchronization primitives are needed to protect critical sections.

Great choice ✅
Race conditions pop up in many places, and once you start spotting them, you’ll see why synchronization is so critical. Let’s go through **practical examples** across different domains.

---

# **1. Bank Account Withdrawal**

```c
int balance = 1000;

void* withdraw(void* arg) {
    int amount = 700;
    if (balance >= amount) {
        balance -= amount;
    }
    return NULL;
}
```

* **Thread A** checks balance (1000 ≥ 700) → true
* **Thread B** also checks balance (1000 ≥ 700) → true
* Both deduct → balance becomes `-400` (overdrawn).

⚠️ This violates the business rule that account balance should never go negative.
👉 A race condition between the `if` check and the deduction.

---

# **2. Logging to a File**

```c
FILE* f = fopen("log.txt", "a");

void* worker(void* arg) {
    fprintf(f, "Thread %ld finished task\n", (long)arg);
    return NULL;
}
```

* Multiple threads write to the same file simultaneously.
* Output may look like:

```
Thread 1 finished task
ThrThread 2 finished task
ead 3 finished task
```

⚠️ The writes **interleave** and corrupt the log file.

--------------

# **Summary of Patterns**

* **Lost updates** → shared counter, balance deduction.
* **Corrupted output** → file logging, console printing.
* **Invalid state** → producer-consumer without lock.
* **Inconsistent hardware state** → kernel register writes.
* **Resource leaks** → cancellation races.

