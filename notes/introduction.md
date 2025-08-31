# CSE 150 - Lecture 1: Course Introduction & What is an Operating System?

---

## Key Concepts

- **What is an OS?**
  - A layer of software between hardware and user applications
  - Provides convenient abstractions and protected access to resources
  - Enables secure and scalable access to storage, memory, CPU, and devices

- **Why study OS?**
  - Foundational for understanding how computers run
  - Required for systems-level programming, backend, security, distributed systems

- **Course Structure**
  - Projects simulate real-world software team environments
  - Topics span threads, scheduling, filesystems, memory, I/O, networking, security

---

## What is an Operating System?

- A **software layer** that:
  - Provides **abstractions**: Files, Threads, Processes
  - Offers **security & protection**
  - Facilitates **hardware communication**
  - Manages **resources**: memory, CPU, storage, I/O

---

## OS Basics

### Virtual Machine Abstraction

- OS acts as an interface between apps and hardware
- Abstracts:
  - Files → Storage
  - Processes → CPU
  - Memory → RAM, Paging
  - Threads → Multiprocessing

### Context Switching

- Multiple processes run concurrently
- OS switches between them
- Protects each process with **memory isolation**

### Loading and I/O

- OS loads instructions from storage to memory
- Handles device I/O with **interrupts**, **polling**, **DMA**

---

## Challenges in OS Design

### Complexity & Scale

- Devices vary in:
  - **Hardware**: sensors → GPUs
  - **Speed**: nanoseconds → seconds
  - **Storage**: KB → TB
  - **Networks**: kbps → gbps

### Questions an OS Must Solve

- Can multiple processes run independently?
- Can faulty programs crash others?
- Can all programs access all hardware?
- Can every program run on every device?

---

## Real-World Impact

### Internet of Things (IoT)

- Embedded devices everywhere
- OS supports:
  - Remote sensing
  - Massive scalability
  - Cloud integration
  - Fault-tolerance and security

---

## Instructor Notes

- Encouraged: Preview slides before lecture, review after
- Read and do the exercises in the textbook
- Ask questions during class and lab

---

## Exam Tips

- Understand terminology, don’t memorize blindly
- Be able to:
  - Explain what an OS does and why it matters
  - Describe abstractions provided by the OS
  - Understand scheduling, memory management, and device management

---

## Key Takeaways

- The OS enables **hardware abstraction**, **resource protection**, and **process isolation**
- Learning OS helps you become a **better systems programmer**
- Projects will simulate **real-world collaboration**
- OS runs on a wide range of devices and scales massively