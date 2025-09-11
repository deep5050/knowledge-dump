# **1. What is a Mutex?**

* **Mutex = MUTual EXclusion lock**.
* Its job: make sure **only one thread** can enter a **critical section** at a time.
* Works like a **lock on a door**:

  * `lock()` → thread enters, door locked.
  * Other threads wait outside.
  * `unlock()` → thread leaves, door unlocked.

---

# **2. How Mutex Fixes Race Conditions**

Without mutex → multiple threads interleave instructions → races.
With mutex → instructions inside critical section execute **atomically** (from the perspective of other threads).

👉 Mutex enforces **serialization**: one thread at a time in a critical section.

---

# **3. Example: Bank Account Withdrawal (Race Condition Fix)**

### Problem Code (race condition):

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

Two threads could both see balance `= 1000`, both withdraw → balance ends at `-400`.

---

### Fixed Code (with Mutex):

```c
#include <stdio.h>
#include <pthread.h>

int balance = 1000;
pthread_mutex_t lock;   // Declare a mutex

void* withdraw(void* arg) {
    int amount = *(int*)arg;

    // Lock the critical section
    pthread_mutex_lock(&lock);

    if (balance >= amount) {
        printf("Withdrawing %d...\n", amount);
        balance -= amount;
        printf("Balance after withdrawal: %d\n", balance);
    } else {
        printf("Insufficient funds! Balance: %d, Tried: %d\n", balance, amount);
    }

    // Unlock so other threads can enter
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int amt1 = 700, amt2 = 700;

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, withdraw, &amt1);
    pthread_create(&t2, NULL, withdraw, &amt2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Balance = %d\n", balance);

    // Destroy mutex when done
    pthread_mutex_destroy(&lock);

    return 0;
}
```

---

### **How this works**

* Thread A calls `pthread_mutex_lock(&lock)` → enters critical section, lock is **taken**.
* Thread B calls `pthread_mutex_lock(&lock)` → sees lock **busy**, so it **blocks** until Thread A unlocks.
* Thread A finishes withdrawal, calls `pthread_mutex_unlock(&lock)`.
* Now Thread B wakes up and executes its withdrawal with the **updated balance**.

---

### **Output (example run)**

```
Withdrawing 700...
Balance after withdrawal: 300
Insufficient funds! Balance: 300, Tried: 700
Final Balance = 300
```

✅ Correct! No negative balance.
Without mutex, you could have gotten `-400`.

---

# **4. Key Points about Mutex**

* Protect **only the critical section**, not the whole function (otherwise performance suffers).
* Must be paired: every `lock` must have a matching `unlock`.
* Deadlock danger: if two threads lock in different orders.

---

# **1. Why does the lock have to be global?**

👉 Because the lock must be **shared by all threads that want to protect the same resource**.

* In the bank example:

  * The shared resource = `balance`.
  * To prevent races, **every thread** that touches `balance` must synchronize using the *same mutex*.

If you made the lock **local (stack variable)** inside each thread’s function:

* Each thread would create its own lock.
* Then Thread A locks its local mutex, Thread B locks its own → both happily enter the critical section at the same time.
* ❌ No actual synchronization (completely useless).

✅ Rule: **One resource → one shared mutex**.

---

# **2. How does a mutex actually block other threads?**

At a high level:

* A mutex is just a small data structure (often an integer or flag) in memory.
* It has states like **Unlocked (0)** and **Locked (1)**.
* When a thread tries to lock:

  1. It performs an **atomic instruction** like `compare-and-swap` or `test-and-set`.
  2. If lock was `0`, it sets it to `1` and continues (thread got the lock).
  3. If lock was already `1`, then:

     * The thread cannot proceed.
     * The OS puts the thread to **sleep** (blocked state).
     * Later, when another thread unlocks, the OS wakes up one of the waiting threads.

---

# **3. CPU Instructions Behind Mutex**

CPUs provide **atomic operations** that can’t be interrupted mid-way:

* `xchg` (exchange)
* `cmpxchg` (compare and exchange)
* `test-and-set`

Example (x86 pseudo-assembly for mutex lock):

```asm
mov eax, 1
lock xchg eax, [mutex]   ; Atomically swap eax with mutex variable
cmp eax, 0
jne wait                 ; If old value wasn’t 0, spin/wait
```

* If `mutex == 0` → eax gets 0, mutex becomes 1 → success.
* If `mutex == 1` → eax gets 1, mutex stays 1 → thread must wait.

This ensures **only one thread can flip 0→1 successfully**.

---

# **4. User-space vs Kernel Involvement**

* If the lock is **free** → acquired using atomic CPU instruction (fast, no kernel).
* If the lock is **contended** (already held) → the OS kernel may step in:

  * The thread is put to sleep (`futex` in Linux).
  * Another thread eventually calls `unlock`.
  * Kernel wakes up a waiting thread.

👉 That’s why mutexes are efficient:

* Fast path (no contention): pure user-space, atomic instruction.
* Slow path (contention): kernel blocks/wakes threads (saves CPU cycles vs busy spin).

---

# **5. Why not just use a local flag?**

If you try:

```c
int locked = 0;

if (!locked) {
   locked = 1;
   // critical section
   locked = 0;
}
```

This doesn’t work because:

* Two threads may both see `locked == 0` at the same time before either sets it to 1.
* Writes to memory aren’t atomic unless you use special CPU instructions.

✅ That’s why mutex uses **hardware-level atomic instructions** + **OS scheduling** to guarantee correctness.

---

# **6. Summary**

* Mutex must be **shared** (global or passed to threads) because it represents ownership of the shared resource.
* Internally, mutex = integer/flag + some bookkeeping.
* CPU atomic instructions enforce “only one can flip the flag”.
* If locked, other threads are **blocked by OS** until it’s free.
* That’s how mutex **serializes** access and removes race conditions.

---

## **2. Why exactly one lock per resource?**

* The mutex is a **ticket** for accessing the resource.
* Only the thread holding the ticket is allowed inside the resource’s critical section.
* If you had multiple separate locks for the same resource:

  * Thread A locks `lock1` → goes in.
  * Thread B locks `lock2` → also goes in.
  * ❌ Both inside at once → race condition still exists!

So, to enforce true mutual exclusion, **all threads must coordinate on the same lock**.

---

## **3. Example: Bank Balance**

Shared resource = `balance`.

### Wrong: each thread has its own lock

```c
void* withdraw(void* arg) {
    pthread_mutex_t local_lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&local_lock);

    if (balance >= 700) {
        balance -= 700;
    }

    pthread_mutex_unlock(&local_lock);
}
```

* Each thread locks **its own local mutex**.
* They don’t see each other’s locks.
* Both enter → race condition still happens.

---

### Correct: one global/shared lock

```c
pthread_mutex_t balance_lock = PTHREAD_MUTEX_INITIALIZER;

void* withdraw(void* arg) {
    pthread_mutex_lock(&balance_lock);

    if (balance >= 700) {
        balance -= 700;
    }

    pthread_mutex_unlock(&balance_lock);
}
```

* Now **all threads compete on the same lock**.
* At most **one thread** can update balance at a time.
* ✅ Race fixed.

---

## **4. Extending the Rule**

* If you have **two independent resources**, you need **two locks**:

  * Example: `balance1` and `balance2` (two accounts).
  * Each should have its own lock, so withdrawals from different accounts can proceed in parallel.

* If you have **one complex resource** (like a queue with head/tail pointers), you still just need **one lock** protecting it.

---

## **5. Why not one global lock for everything?**

You could, but:

* That would serialize **all threads**, even if they touch different resources.
* This kills concurrency and performance.
* Better: use **one lock per resource** so unrelated operations can run in parallel.

---

✅ **Golden Rule**:

* **Too few locks** (one per thread) → no synchronization, races.
* **Too many locks** (one global for everything) → safe but slow.
* **Right number of locks = one per resource** (or per independent resource).

---
