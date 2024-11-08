### **Project Title: Philosophers**

**Project Overview:**
The "Philosophers" project is a classic concurrency and synchronization problem where a set of philosophers are seated around a table. Each philosopher can either think or eat spaghetti, and the goal is to simulate this scenario while ensuring the philosophers can operate concurrently without deadlock or starvation. The challenge lies in managing shared resources (forks) between the philosophers and ensuring they can eat and think without conflicts.

**Objective:**
The objective of this project is to implement a simulation where a set number of philosophers share a limited number of forks. Philosophers alternate between thinking and eating, but they must pick up and put down forks to eat. The goal is to design a system that ensures philosophers can eat without running into issues like deadlock (where all philosophers are waiting on each other to release a fork) or starvation (where some philosophers never get to eat).

### **Key Features:**
1. **Concurrency**: The program simulates multiple philosophers (threads) thinking and eating simultaneously.
2. **Synchronization**: Philosophers share resources (forks), and the challenge is to synchronize access to these resources to avoid conflicts.
3. **Deadlock Prevention**: The program must prevent deadlock, where all philosophers are waiting on each other indefinitely.
4. **Starvation Prevention**: The program must ensure that no philosopher is indefinitely denied the chance to eat (i.e., starvation).
5. **Thread Management**: Philosophers are implemented as threads that will interact with each other through mutexes or semaphores to safely access the shared forks.

### **Functionality:**
- Philosophers are represented as threads that continuously alternate between thinking and eating.
- Each philosopher needs two forks to eat, and there is one fork between each pair of philosophers.
- The simulation should ensure that when a philosopher wants to eat, they can pick up both forks if available and put them down when finished.
- The program must ensure no deadlock occurs (e.g., when all philosophers hold one fork and wait for the other) and prevent starvation by ensuring fairness in fork allocation.
  
### **Key Concepts:**
- **Mutexes and Semaphores**: These synchronization tools are used to manage access to shared resources (forks) and ensure that only one philosopher can access a fork at a time.
- **Pthreads**: The philosophers are implemented as threads using the POSIX threads library (`pthreads`), which handles thread creation, synchronization, and communication.
- **Time Management**: Philosophers think and eat for specified durations, and the program should control the timing to simulate realistic behavior.
  
### **Challenge Areas:**
- **Deadlock**: Designing the system to avoid situations where philosophers block each other indefinitely.
- **Starvation**: Ensuring that all philosophers are able to eat in a reasonable amount of time and none are left hungry due to unfair scheduling.
- **Concurrency**: Managing multiple threads with shared resources and synchronizing their actions properly to ensure correctness.

### **Expected Outcomes:**
- A successful implementation where philosophers can eat and think without encountering deadlocks or starvation.
- A well-designed multi-threaded solution that showcases effective use of synchronization mechanisms.
- A robust solution that handles edge cases like limited resources and ensures fair access to forks for all philosophers.
