
# **1. What is Deadlock?**

A **deadlock** occurs when two or more threads are **waiting forever** for each other to release resources, so none of them can make progress.

Think of it as a **traffic gridlock**:

* Car A blocks the intersection and waits for Car B to move.
* Car B blocks the other lane and waits for Car A.
* Neither can move → stuck forever.

---

# **2. How Deadlock Forms (Coffman’s 4 Conditions)**

A deadlock happens only if **all four conditions** are true:

1. **Mutual Exclusion** → only one thread can hold a lock at a time.
2. **Hold and Wait** → a thread holds one lock and waits for another.
3. **No Preemption** → a lock can only be released voluntarily.
4. **Circular Wait** → a cycle exists (Thread A waits for Thread B, which waits for Thread A).

If all four hold → deadlock possible.

---

# **3. Example of Deadlock with Two Bank Accounts**

```c
void transfer(BankAccount* from, BankAccount* to, int amount) {
    pthread_mutex_lock(&from->lock);  // Thread A locks acc1
    sleep(1);                         // Artificial delay to increase chance
    pthread_mutex_lock(&to->lock);    // Thread A waits for acc2

    // transfer logic ...
    pthread_mutex_unlock(&to->lock);
    pthread_mutex_unlock(&from->lock);
}
```

Scenario:

* Thread A wants to transfer from acc1 → acc2.
* Thread B wants to transfer from acc2 → acc1.

**Timeline:**

1. Thread A locks acc1.
2. Thread B locks acc2.
3. Thread A tries to lock acc2 (blocked).
4. Thread B tries to lock acc1 (blocked).

Both are waiting → **deadlock**.

---

# **4. How to Solve / Prevent Deadlock**

There are **four strategies**:

### ✅ **1. Lock Ordering (Most Common)**

* Always acquire multiple locks in a **predefined order**.
* Example: always lock `acc1` before `acc2` if `acc1 < acc2`.
* Breaks the **circular wait** condition → no deadlock.

(This is what we used in the two-account code earlier).

---

### ✅ **2. Trylock + Backoff**

* Instead of blocking forever, try to acquire a lock, if not succss **release already takes locks**

```c
if (pthread_mutex_trylock(&lock2) != 0) {
    // Couldn’t get lock, release what I hold and retry later
    pthread_mutex_unlock(&lock1);
    sleep(1);
    goto retry;
}
```

* This way, threads back off instead of waiting forever.

---

### ✅ **3. Timeout Locks**

* Some APIs support **timed locks**:

```c
pthread_mutex_timedlock(&lock, &ts);
```

* If lock not acquired in X seconds → give up.

---

### ✅ **4. Avoid Hold-and-Wait**

* Request **all resources at once** instead of one by one.
* Example: wrap both account locks in one "transaction lock".

---

# **5. Detecting Deadlocks**

* Tools: **Helgrind**, **ThreadSanitizer (TSan)**, or kernel logs in driver code.
* Symptoms: program hangs, CPU idle, threads stuck in `pthread_mutex_lock`.

---

# **6. Summary**

* **Deadlock = threads waiting on each other forever.**
* Caused by circular wait and multiple locks.
* Fixes:

  * Consistent **lock ordering** (best practice).
  * Use **trylock/backoff**.
  * Use **timeouts**.
  * Acquire all needed resources at once.

---
## Note: why a processing delay of sleep(1) is introduced to simulate deadlock

I added the **`sleep(1)` delay** only to **make the deadlock more likely to happen** when you run the program.

Here’s why:

* Without the delay, modern CPUs execute instructions **very fast**. **Thread 1 might finish locking both accounts before Thread 2 even starts**, so the deadlock doesn’t appear every time.
* By inserting a `sleep(1)`, we force Thread 1 to **pause after locking the first account**, giving Thread 2 enough time to grab the other account’s lock.
* This sets up the “perfect race condition” → both threads are now holding one lock and waiting for the other → deadlock.

So in summary:

* **With delay** → deadlock is almost guaranteed → good for demo.
* **Without delay** → deadlock may or may not happen (depends on scheduling and timing).

👉 It’s like putting two cars in a one-lane bridge:

* If one car enters much earlier, no deadlock.
* If both enter at the same time → stuck face-to-face forever.

Would you like me to show the **same banking example without the delay** and then explain how the OS thread scheduler decides whether deadlock will appear?

## Good to know
The **order of unlocking does not matter**, only the **order of locking does**.

Here’s why:

---

### 🔐 Locking order is critical

* Deadlock happens when two (or more) threads **grab locks in different orders**.
* Example:

  * Thread 1 → locks `acc1`, waits for `acc2`.
  * Thread 2 → locks `acc2`, waits for `acc1`.
    → Circular wait → **deadlock**.
* If all threads follow the same **locking order** (say: always lock `acc1` before `acc2`), deadlock cannot happen.

---

### 🔓 Unlocking order is not critical

* Once a thread is done with its critical section, it releases the locks.
* The waiting thread can then proceed.
* Whether you unlock `acc1` before `acc2` or vice versa doesn’t cause deadlock, because:

  * Unlock is a **non-blocking operation** (it just makes the mutex available again).
  * No other thread is “waiting to unlock,” they’re only waiting to **lock**.

---

💡 In practice:

* Developers usually unlock in the **reverse order of locking** (like a stack: last acquired, first released).
* This isn’t required for correctness, but it keeps code cleaner and easier to reason about.

---

👉 So:

* **Lock order matters** (to prevent circular wait).
* **Unlock order doesn’t matter** (but reverse order is a common convention).

---

Do you want me to show you a **deadlock-free version of the banking transfer code** with proper lock ordering, so you see the difference in action?
