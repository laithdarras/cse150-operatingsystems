# Lecture 12 – Midterm Review (March 10, 2025)

---

## Exam Format & Strategy

- **Midterm Date**: Wednesday, March 12, 2025
- **Coverage**: Slides 1–12, Textbook Chapters 1–7
- **Cheat Sheet**: One page, double-sided, handwritten allowed
- **Calculator**: Allowed
- **Grading Focus**: TA and professor will **grade based on keywords**
- **Write very clear answers** so graders can spot keywords easily
- **Use bullets or label steps** where possible

---

## High-Yield Focus Areas

### Four Fundamental OS Concepts (1 guaranteed question!)
1. **Threads**
   - Unique execution context
   - Program Counter (PC), Stack, Registers
2. **Address Space**
   - Memory abstraction for processes
   - Isolation, protection, layout (text, heap, stack)
3. **Process**
   - An instance of an executing program
   - One or more threads share an address space
4. **Dual-Mode Operation (Protection)**
   - System mode (kernel), User mode
   - Mode bit distinguishes privilege level

---

## Processes & Threads

- Context switching between processes is expensive (entire memory state + CPU state)
- Threads are **lightweight**: switch only CPU context, not memory space
- Threads share:
  - Code segment
  - Data segment
  - Heap
  - But each has its own stack!

---

## Mode Transfers

**3 Types of Mode Transfer:**
1. **System Call**: User → Kernel (e.g., file read)
2. **Interrupt**: External signal (e.g., timer, I/O)
3. **Exception / Trap**: Fault in execution (e.g., divide by zero)

---

## Why Threads Don't Run Forever

- **Threads don’t run forever** due to:
  - **Timer interrupts**: force switch based on scheduling policy
  - **Voluntary yields**
  - **Blocking operations** (e.g., I/O wait)

---

## Scheduling & Ready Queue

- Threads wait in a **ready queue**
- Scheduler chooses one based on **scheduling algorithm**
- Scheduling algorithms discussed:
  - **FCFS (First Come First Serve)**
  - **SJF (Shortest Job First)**
  - **SRTF (Shortest Remaining Time First)**
  - **Round Robin**
  - **Multi-Level Feedback Queue (MLFQ)**
  - **Lottery Scheduling**

**Key scheduling question**:
- Given a list of processes with arrival and burst times, calculate:
 - Waiting time for each process
 - Average waiting time

**Know when to use which algorithm, pros/cons, and fairness**

---

## Synchronization & Concurrency

### **Too Much Milk Problem**
- Multi-threaded access to shared resource
- Classic example of **race condition**
- Know the evolution:
  - **Naive (incorrect)**
  - **Flags** – busy waiting but better
  - **Turn-based** – inefficient
  - **Peterson’s Algorithm** – correct for 2 threads
    - **Fails for 3+ users** due to complex interactions
- Understand: busy waiting, correctness, and why each version is improved

---

### Locks

- Implement **mutual exclusion** (only one thread in critical section)
- Use:
  - `acquire()` / `release()` methods
  - `testAndSet` or atomic swap primitives
- Avoid **disabling interrupts** unless in kernel mode
- Sleep-waiting better than busy waiting

---

### Semaphores

- Two methods:
  - `P()` or `wait()`
  - `V()` or `signal()`
- Used for:
  - Mutual exclusion (binary semaphore)
  - Resource tracking (counting semaphore)

---

### Monitors

- High-level abstraction using:
  - **Condition variables**: `wait()`, `signal()`, `broadcast()`
  - Only one thread active inside monitor at a time
- Be ready to **fill in blanks in code snippet** (based on reader/writer problem)

**Put full Reader & Writer code on cheat sheet**  
Know how it protects database access through synchronized read/write logic

---

## Deadlock

### Deadlock Detection

- Use a **resource allocation graph**
- Detect **cycles** or run **Deadlock Detection Algorithm** (step-by-step resource matching)

### Banker’s Algorithm

- Safety check algorithm
- Will **NOT** grant request if it leads to unsafe state
- Know:
  - **Max**, **Allocation**, **Need**, **Available**
  - How to simulate safe state check
- Note: It **allows the sum of max needs > total resources**, as long as it **doesn't cause deadlock**

---

## Producer-Consumer & Threaded Code

- **Bounded Buffer Problem**
- Use three semaphores:
  - `mutex` (binary)
  - `emptyBuffers` (counting)
  - `fullBuffers` (counting)
- Be ready to:
  - Write/complete correct producer/consumer code
  - Identify **incorrect orderings that lead to deadlock**

Write correct version of Producer/Consumer code on cheat sheet  
List intermediate steps and `x` values like in HWs

---

## Tips for Exam

- **WRITE KEYWORDS CLEARLY** — grader will look for them!
- Use **bullet points**
- Show your work for all calculations
- If doing thread trace or semaphore updates:
  - Label each step clearly (`P()`, `V()`, thread name, updated value)

---

## Cheat Sheet Sections

- Four OS Concepts + Definitions
- Diagram of Address Space + Stack/Heap Layout
- Code for Too Much Milk (2-thread version)
- Lock pseudocode using testAndSet
- Semaphore logic and use-cases
- Full Reader and Writer (monitor-based) code
- Deadlock Detection Algorithm (code + chart format)
- Banker’s Algorithm walkthrough
- Scheduling: All algorithms + example waiting time calc

---

Let’s crush this midterm :D