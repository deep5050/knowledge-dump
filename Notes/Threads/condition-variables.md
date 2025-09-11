## 🔹 1. Condition variables

A **Condition Variable** is a synchronization primitive that allows **threads to wait for some condition to become true**.

* Threads can **sleep** instead of busy-waiting, saving CPU cycles.
* CondVars are **always used with a mutex**, because you need to protect shared data while checking/updating the condition.

---

### Key Operations

| Operation   | Description                                                                                                                     |
| ----------- | ------------------------------------------------------------------------------------------------------------------------------- |
| `wait`      | Thread releases the mutex and **sleeps** until another thread signals the condition. After waking, it **reacquires the mutex**. |
| `signal`    | Wakes **one** waiting thread.                                                                                                   |
| `broadcast` | Wakes **all** waiting threads.                                                                                                  |

---

### 🔹 Why not just use busy-wait?

Busy-waiting example:

```c
while(flag == 0); // spins forever, wastes CPU
```

Problems:

* CPU cycles wasted.
* Poor scalability with many threads.

**Condition variables** solve this by letting the thread **sleep until the condition is met**.

---

### 🔹 Example Analogy

* Think of a **restaurant kitchen**:

  * Thread = waiter
  * Mutex = protects access to the order list
  * Condition Variable = “new order arrived”

Waiter thread waits on the cond var until a new order is placed, instead of constantly checking the list.

---

### 🔹 Typical Pattern

1. Lock mutex.
2. While (condition not met) → `cond_wait()` → **releases mutex and sleeps**.
3. When condition met → proceed with critical section.
4. Unlock mutex.

Producer-consumer example (simplified):

```c
pthread_mutex_lock(&mutex);
while(buffer_empty()) {
    pthread_cond_wait(&cond, &mutex); // releases mutex & sleeps
}
// buffer has data, consume it
pthread_mutex_unlock(&mutex);
```

* Producer thread signals:

```c
pthread_mutex_lock(&mutex);
// add data to buffer
pthread_cond_signal(&cond); // wakes one waiting consumer
pthread_mutex_unlock(&mutex);
```

---

### 🔹 Key Points

1. **Always use with a mutex** → protects the shared state.
2. **Wait releases the mutex while sleeping**, then reacquires it before returning.
3. **signal vs broadcast** → signal wakes 1 thread, broadcast wakes all.
4. Avoid busy-waiting → saves CPU and improves efficiency.

----
Perfect! Let’s build a **full producer-consumer example** using **mutex + condition variables**. This will tie together everything you’ve learned so far.

---

## 🖥️ Producer-Consumer with Condition Variables

* Shared buffer of fixed size (like a queue).
* **Producers** add items.
* **Consumers** remove items.
* **Mutex** protects the buffer.
* **Condition variables** signal when buffer is not empty (consumer) or not full (producer).

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCERS 2
#define CONSUMERS 2
#define ITEMS_TO_PRODUCE 10

int buffer[BUFFER_SIZE];
int count = 0; // number of items in buffer

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;

// Producer thread
void* producer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        pthread_mutex_lock(&mutex);

        // Wait until buffer has space
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_not_full, &mutex);
        }

        // Add item
        buffer[count++] = i;
        printf("Producer %d: produced %d, buffer count = %d\n", id, i, count);

        // Signal consumer that buffer is not empty
        pthread_cond_signal(&cond_not_empty);

        pthread_mutex_unlock(&mutex);
        sleep(1); // simulate work
    }
    return NULL;
}

// Consumer thread
void* consumer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        pthread_mutex_lock(&mutex);

        // Wait until buffer has items
        while (count == 0) {
            pthread_cond_wait(&cond_not_empty, &mutex);
        }

        // Remove item
        int item = buffer[--count];
        printf("Consumer %d: consumed %d, buffer count = %d\n", id, item, count);

        // Signal producer that buffer has space
        pthread_cond_signal(&cond_not_full);

        pthread_mutex_unlock(&mutex);
        sleep(2); // simulate work
    }
    return NULL;
}

int main() {
    pthread_t prod[PRODUCERS], cons[CONSUMERS];
    int ids[PRODUCERS > CONSUMERS ? PRODUCERS : CONSUMERS];

    for (int i = 0; i < PRODUCERS; i++) {
        ids[i] = i;
        pthread_create(&prod[i], NULL, producer, &ids[i]);
    }

    for (int i = 0; i < CONSUMERS; i++) {
        ids[i] = i;
        pthread_create(&cons[i], NULL, consumer, &ids[i]);
    }

    for (int i = 0; i < PRODUCERS; i++) pthread_join(prod[i], NULL);
    for (int i = 0; i < CONSUMERS; i++) pthread_join(cons[i], NULL);

    return 0;
}
```

---

## 🔍 How it works

1. **Producer**

   * Locks mutex.
   * If buffer is full → `pthread_cond_wait(&cond_not_full, &mutex)` → sleeps and releases mutex.
   * Adds item, signals consumer → `pthread_cond_signal(&cond_not_empty)`.
   * Unlocks mutex.

2. **Consumer**

   * Locks mutex.
   * If buffer empty → `pthread_cond_wait(&cond_not_empty, &mutex)` → sleeps and releases mutex.
   * Removes item, signals producer → `pthread_cond_signal(&cond_not_full)`.
   * Unlocks mutex.

3. **Avoid busy-waiting**

   * Threads sleep while waiting → CPU cycles saved.

---
Ah! This is **one of the most important subtleties** in condition variables. Let’s break it down carefully.

---

## 🔹 Why `while()` around `pthread_cond_wait()`?

The pattern you always see is:

```c
pthread_mutex_lock(&mutex);
while (condition_not_met) {
    pthread_cond_wait(&cond_var, &mutex);
}
// now condition is true, proceed
pthread_mutex_unlock(&mutex);
```

---

### 1️⃣ Condition can be **spurious**

* Sometimes, `pthread_cond_wait()` **returns even if no thread called `pthread_cond_signal()`**.
* This is called a **spurious wakeup**.
* If you just use `if`, your thread might continue **even though the condition isn’t actually met**, causing race conditions.

```c
if (buffer_empty()) {
    pthread_cond_wait(&cond_not_empty, &mutex); // could wake up even if empty
}
// unsafe: buffer might still be empty
```

* Using `while` ensures the thread **rechecks the condition** after waking up.

---

### 2️⃣ Multiple threads waiting on the same condition

* Suppose 3 consumers are waiting for items, and producer signals **once**.
* **Only one thread can actually consume** the item.
* The other threads wake up but the condition (`buffer not empty`) might **no longer hold**.
* `while` ensures threads that wake up **re-check the condition** before entering critical section.

---

### 🔹 What happens step by step

1. Thread locks mutex.
2. Checks condition → `while(buffer_empty())`.
3. Buffer empty → calls `pthread_cond_wait()`.

   * **Releases mutex** and sleeps.
4. Producer adds an item and calls `pthread_cond_signal()`.
5. Waiting thread wakes up → reacquires mutex.
6. **Re-checks `while(buffer_empty())`**:

   * If still empty (spurious wakeup or another consumer already consumed) → go back to wait.
   * If not empty → proceed.

---

### ✅ Key Rule

> **Always use a loop around `pthread_cond_wait()`. Never an `if`.**

* Protects against **spurious wakeups**.
* Handles **multiple threads waiting on the same condition** safely.
* Ensures **thread only proceeds when condition is truly satisfied**.

---
Ah! This is a **key detail of how `pthread_cond_wait()` works internally** — it’s a bit magical if you only look at the code. Let’s clarify.

---

## 🔹 What happens inside `pthread_cond_wait(&cond, &mutex)`

When a thread calls:

```c
pthread_cond_wait(&cond, &mutex);
```

**Several things happen atomically inside the system:**

1. **Mutex is released automatically.**

   * You **don’t need to unlock it manually**.
   * This is crucial because otherwise, the signaling thread could never acquire the mutex to change the condition.

2. **Thread is put to sleep** (blocked) until another thread calls `pthread_cond_signal()` or `pthread_cond_broadcast()`.

3. When the thread **wakes up**, it **reacquires the mutex automatically** **before returning** from `pthread_cond_wait()`.

4. Execution **resumes right after the `pthread_cond_wait()` call**, not from the beginning of the function.

---

### 🔹 So the flow looks like:

```c
pthread_mutex_lock(&mutex);

while(buffer_empty()) {
    // THIS LINE:
    pthread_cond_wait(&cond_not_empty, &mutex); 
    // releases mutex and sleeps
    // wakes up -> reacquires mutex automatically
}
// after waking up and reacquiring mutex, execution resumes here
consume_item();
pthread_mutex_unlock(&mutex);
```

* You **never lose your place** — you resume **after the `pthread_cond_wait()`** line.
* The mutex is held again automatically when you wake up, so you can safely access shared data.

---

### 🔹 Why you don’t see explicit `unlock()`:

* `pthread_cond_wait()` is designed to **atomically release the mutex and sleep** in one step.
* This is what allows another thread to safely acquire the mutex and modify the condition (e.g., add an item to the buffer).
* If it didn’t do this, **deadlock** would happen because the waiting thread would hold the mutex while sleeping.

---

### 🔹 Analogy

* Think of it like a **magical “pause” button**:

  1. You press `cond_wait()`.
  2. While paused, you **automatically let go of the lock** so others can work.
  3. When someone signals, you **resume exactly where you paused** and automatically **grab the lock again**.

---


