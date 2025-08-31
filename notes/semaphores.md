# CSE 150 – Lecture 8: Semaphores and Monitors

---

## Key Concepts

- Semaphores are generalized locks
- Semaphores use `P()` and `V()` operations (Dutch: proberen = test, verhogen = increment)
- Monitors = Lock + Condition Variables
- Critical section protection must use atomic operations
- Producer-Consumer (Bounded Buffer) Problem
- Order of `P()` and `V()` operations affects **deadlock** and **scheduling**
- Monitor implementation improves clarity and correctness over semaphores

---

## Lecture Notes

### Locks by Disabling Interrupts
```c
Acquire() {
  disable interrupts;
  if (value == 1) {
    put thread on wait-queue;
    go to sleep();
  } else {
    value = 1;
    enable interrupts;
  }
}

Release() {
  disable interrupts;
  if (wait queue not empty)
    wake thread from wait-queue;
  else
    value = 0;
  enable interrupts;
}
```
- Disabling interrupts ensures atomicity but halts all other system activity.

### Locks using test&set
```c
while (test&set(guard)); // Busy wait

if (value == 1) {
  put thread on wait-queue;
  go to sleep();
  guard = 0;
} else {
  value = 1;
  guard = 0;
}
```
- Threads may busy wait.
- Useful atomic primitive but inefficient without sleeping.

---

# Synchronization Roadmap

| Level         | Mechanism        | Goal                      |
|---------------|------------------|---------------------------|
| Hardware      | Load/Store        | Basic memory operations   |
| Intermediate  | Test&Set, Swap    | Atomic primitives         |
| User-level    | Locks             | Mutual exclusion          |
| Higher-level  | Semaphores        | Mutex + scheduling        |
| Highest       | Monitors          | Structured synchronization|

---

## Semaphores

- Created by Dijkstra (the legendary computer scientist)  
- Integer value >= 0  
- Two atomic operations:
  - `P()` – Wait until value > 0, then decrement
  - `V()` – Increment value and wake up one waiting thread

### Use Cases:
- **Mutual exclusion**: `value = 1`
- **Scheduling constraints**: `value = 0`

---

## Producer-Consumer Problem

**Problem**: Shared buffer of fixed size, producer adds, consumer removes

### Constraints:
- Consumer waits if buffer empty  
- Producer waits if buffer full  
- Only one thread accesses the buffer at a time (mutual exclusion)

### Semaphore Solution:
```c
Semaphore fullSlots = 0;
Semaphore emptySlots = BUF_SIZE;
Semaphore mutex = 1;
```

### Producer
```c
emptySlots.P();   // Wait for space
mutex.P();        // Lock
Enqueue(item);    
mutex.V();        // Unlock
fullSlots.V();    // Signal consumer
```

### Consumer
```c
fullSlots.P();    // Wait for item
mutex.P();        // Lock
item = Dequeue();
mutex.V();        // Unlock
emptySlots.V();   // Signal producer
```

---

### Order of P() & V() Operations
- Deadlock Risks:
    - If mutex.P() before emptySlots.P() → potential deadlock
    - Correct order: wait for resource, then lock mutex

- V() Order:
    - Can be flexible but affects performance
    - Should release resources before waking threads for better scheduling

---

### Monitors & Condition Variables
- Monitor = Lock + Condition Variables
- Languages like Java use synchronized keyword
- In Nachos: implement using explicit Lock and Condition

### Condition Variable Operations
- wait(&lock) – Releases lock and sleeps
- signal() – Wakes one waiting thread
- broadcast() – Wakes all waiting threads

> You must hold the lock when calling these!

---

### Monitor Example
```c
Lock lock;
Condition dataReady;
Queue queue;

AddToQueue(item) {
  lock.Acquire();
  queue.enqueue(item);
  dataReady.signal();
  lock.Release();
}

RemoveFromQueue() {
  lock.Acquire();
  while (queue.isEmpty()) {
    dataReady.wait(&lock);
  }
  item = queue.dequeue();
  lock.Release();
  return item;
}
```

---

### Instructor Notes
- Semaphores are powerful but hard to reason about
- Monitors make code clearer and safer
- Use one semaphore per constraint
- Semaphores combine mutex + scheduling, which leads to complexity

---

### Key Takeaways
- Semaphores: Low-level, powerful, but tricky
- Monitors: High-level, safer, easier to reason about
- Always use one semaphore per constraint
- Correct synchronization requires:
    - Mutual exclusion (mutex)
    - Scheduling coordination (signal/wait)
- Deadlock occurs from improper ordering of P() calls