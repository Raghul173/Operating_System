# Operating Systems Lab

A comprehensive repository for Operating Systems laboratory experiments and curriculum practicals.

## Table of Contents
* [List of Exercises](#list-of-exercises)
* [Theoretical Topics Covered](#theoretical-topics-covered)
* [References](#references)

---

## List of Exercises

### [Exercise 1: Process Creation using `fork()` and `exec()` System Calls](#exercise-1-process-creation-using-fork-and-exec-system-calls)
* Process lifecycle management and PID tracking.
* Child process creation with `fork()`.
* Loading and executing external programs using the `exec()` family of system calls.

### [Exercise 2: Inter-Process Communication (IPC) using Pipes](#exercise-2-inter-process-communication-ipc-using-pipes)
* Unidirectional communication between related processes.
* Half-duplex and full-duplex communication models.

### [Exercise 3: IPC using Shared Memory and Message Queues](#exercise-3-ipc-using-shared-memory-and-message-queues)
* **Shared Memory:** POSIX/System V shared memory creation, attachment, and synchronization.
* **Message Queues:** Message-based asynchronous communication between processes.

### [Exercise 4: CPU Scheduling Algorithms](#exercise-4-cpu-scheduling-algorithms)
* First-Come, First-Served (FCFS)
* Shortest Job First (SJF) (Preemptive and Non-Preemptive)
* Priority Scheduling (Preemptive and Non-Preemptive)
* Round Robin (RR)

### [Exercise 5: Solving Synchronization Problems using Semaphores](#exercise-5-solving-synchronization-problems-using-semaphores)
* Mutual exclusion implementation using counting and binary semaphores.
* Classic synchronization problems:
  * Producer-Consumer Problem
  * Readers-Writers Problem
  * Dining Philosophers Problem

### [Exercise 6: Deadlock Avoidance Algorithm](#exercise-6-deadlock-avoidance-algorithm)
* Implementation of **Banker's Algorithm**:
  * Safety Algorithm
  * Resource-Request Algorithm

### [Exercise 7: Contiguous Memory Allocation Techniques](#exercise-7-contiguous-memory-allocation-techniques)
* Dynamic storage-allocation strategies:
  * First Fit
  * Best Fit
  * Worst Fit

### [Exercise 8: Page Replacement Algorithms](#exercise-8-page-replacement-algorithms)
* Simulation of demand paging and page fault tracking:
  * First-In, First-Out (FIFO)
  * Least Recently Used (LRU)
  * Optimal Page Replacement (OPT)

### [Exercise 9: Disk Scheduling Algorithms](#exercise-9-disk-scheduling-algorithms)
* Minimizing total seek time with:
  * FCFS
  * SSTF (Shortest Seek Time First)
  * SCAN / C-SCAN
  * LOOK / C-LOOK

### [Exercise 10: File Allocation Techniques](#exercise-10-file-allocation-techniques)
* Sequential / Contiguous Allocation
* Linked Allocation
* Indexed Allocation

---

## Theoretical Topics Covered
* Process lifecycle and context switching
* IPC mechanisms and concurrency control
* CPU performance metrics (Turnaround, Waiting, and Response times)
* Race conditions and critical section resolution
* Deadlock characterization, prevention, and avoidance
* Fragmentation (Internal & External) and memory management
* Page fault handling and replacement efficiency
* Disk arm movement optimization
* Secondary storage allocation efficiency

---

## References
1. *Operating System Concepts Essentials* (10th Ed.) – Silberschatz, Galvin, Gagne
2. *Modern Operating Systems* (4th Ed.) – Andrew S. Tanenbaum, Herbert Bos
3. *Operating Systems: Internals and Design Principles* (9th Ed.) – William Stallings
4. *Operating Systems: A Concept-based Approach* (2nd Ed.) – Dhananjay M. Dhamdhere
5. *Operating Systems: A Design-Oriented Approach* – Charles Crowley
