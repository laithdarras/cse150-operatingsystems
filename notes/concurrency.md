# CSE 150 – Lecture 04 & 05: Concurrency & Thread Dispatching

---

## Key Concepts

- **Processes vs Threads**
- **Thread State & Control**
- **Ready Queues & Scheduling Policies**
- **Thread Dispatching**
- **Dispatch Loop**
- **ThreadFork, ThreadJoin**
- **Interrupt Management & Yielding**
- **Stack growth and thread setup**
- **Multiprogramming & Thread Switching**
- **Project 1 Relevance**

---

## Lecture Notes

### Process vs Thread

- A **process** is composed of:
  - **Code** (instructions)
  - **Memory** (stack, heap, data segments)
  - **I/O state**
  - **CPU registers**
- A **thread** is the smallest unit of execution inside a process.
  - Each thread maintains its **own CPU state** (PC, registers, stack pointer).
  - Multiple threads **share the process address space** (code, heap, I/O resources).

#### Why Threads?
- Threads are **cheaper to create and switch** than processes.
- Threads allow for **parallelism** within a program.
- Used in operating systems for **multiprogramming** while preserving **protection** boundaries.
- Example: Web server handling multiple requests with a thread pool.

---

### Single vs Multi-threaded

| Property        | Single Threaded                 | Multi Threaded                      |
|----------------|----------------------------------|--------------------------------------|
| Memory Access   | Simple                           | Shared memory between threads        |
| CPU Utilization | Limited                          | Better CPU utilization               |
| Switching Cost  | Process-level (heavy)            | Thread-level (lightweight)           |
| Use Case        | Simpler programs                 | Servers, interactive apps, I/O-heavy |

---

### Ready Queues and Scheduling

- **Ready Queue**: Stores threads ready to run.
- Implemented via **linked lists** in Nachos (not arrays, per Project 1).
- Linked list makes **insertions/removals efficient**, but is more error-prone.
- **Dispatching Policies**:
  - **FIFO**: First-In-First-Out (like lines at a coffee shop)
  - **LIFO**: Last-In-First-Out (stack-like)
  - **Priority**: Highest priority runs first

> **Why different scheduling schemes?**  
> OS designers must choose based on goals: minimize response time, fairness, CPU utilization, etc.

---

### Dispatch Loop (OS Control Loop)

- Main OS loop (like `main()` in C)
```c
while (true) {
    RunThread();
    ChooseNextThread();
    SaveState(curTCB);
    LoadState(newTCB);
}
```

- `Yield()`: Function used to voluntarily give up the CPU
- Allows the OS to dispatch another thread
- `ThreadHouseKeeping()`: Cleans up thread resources before switching

---

### Thread Lifecycle

1. Fork: Create a new thread (ThreadFork)
2. Initialize stack and control block
3. Ready: Thread placed in the ready queue
4. Run: Scheduler picks it for execution
5. Yield: Voluntarily gives up CPU
6. Sleep/Blocked: Waiting for an event (e.g., I/O)
7. Finish: Terminates; resources cleaned

### ThreadJoin

- Allows one thread to wait for another to complete.
- Enables parent-child synchronization.

---

### Stack Growth & Context Switching

- Each thread gets its own stack
    - Stack initialized when the thread is created
    - Used to store local variables, return addresses, etc.

- When switching:
    - Save current thread's CPU state (registers, stack pointer)
    - Load new thread’s CPU state

---

### Interrupts & OS Control

- Interrupts: External hardware signals to CPU (e.g., timer interrupt)
- The OS can enable or disable specific interrupts
    - Used to implement atomic operations and critical sections
- Interrupts have priorities
    - Example: Timer > I/O > Software signals

---

### Project 1 Tips

- You will implement your own thread system in Nachos
- Focus areas:
    - Thread creation and dispatch logic
    - Ready queue using linked list
    - Implement yield, sleep, join, and fork
- Understand how stack and context is initialized

---

### Key Takeaways

- Threads provide lightweight concurrency within a process.
- OS uses queues to manage ready threads and dispatch them based on policy.
- Stack and registers are per-thread, while memory is per-process.
- Thread switching is fast and used to implement scheduling.
- You will implement thread management in Nachos Project 1.