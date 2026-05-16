*This project has been created as part of the 42 curriculum by vborysov.*





# Description
This project simulates a group of coders working concurrently in a shared co-working hub. Each coder repeatedly alternates between three activities: compiling, debugging, and refactoring. To compile quantum code, a coder must acquire two shared USB dongles — one from the left side and one from the right side. Since the number of dongles is limited and shared among all coders, proper synchronization is required to prevent conflicts, deadlocks, and starvation.
The main goal of the project is to model concurrent resource sharing using multithreading and synchronization primitives. The simulation must ensure that coders can safely access shared resources while avoiding burnout, which occurs if a coder is unable to compile within a specified amount of time.

The project demonstrates fundamental concepts of concurrent programming, including:
1. thread management;
2. mutex synchronization;
3. resource allocation;
4. race condition prevention;
5. deadlock avoidance;
6. starvation handling;
7. Each coder acts independently without direct communication with others, making synchronization and timing management the core challenges of the simulation.

## Blocking cases handled
### Deadlock prevention

Deadlocks are prevented using a combination of strategies:

- **Ordered resource acquisition**: each coder always checks and acquires dongles in a strict and consistent order, preventing circular wait conditions.
- **Simultaneous availability check**: a coder only proceeds to lock dongles if both required resources are available at the same time, reducing partial locking states.
- **Consistent locking order**: all coders follow the same locking sequence, ensuring that no cyclic dependency between threads can occur.
- **Staggered start (offset execution)**: coders are launched in a staggered / “checkerboard” pattern, reducing contention at startup and preventing immediate lock competition spikes.

These mechanisms together eliminate the Coffman circular wait condition, which is required for deadlock to occur.

### Monitor and lifecycle supervision

A dedicated **monitor thread** supervises the entire simulation and is responsible for ensuring both system liveness and correct termination conditions.

The monitor continuously tracks each coder’s state and performs two key checks:

- **Burnout detection**: it verifies that no coder exceeds the allowed `burnout` time without successfully compiling. If this condition is violated, the simulation is immediately stopped.
- **Completion tracking**: it monitors whether all coders have completed the required number of compile cycles (`compiles`). Once every coder has reached the required amount, the simulation is gracefully terminated.

The monitor operates independently from coder threads and does not interfere with their execution flow. It relies on shared, thread-safe state updated by each coder after key events (compile, debug, refactor).

This design ensures:

- centralized supervision of global termination conditions;
- accurate detection of both failure (burnout) and success (all tasks completed);
- no direct communication between coders;
- minimal synchronization overhead while maintaining correctness.

### Log serialization

All runtime output is serialized using a dedicated global mutex stored in the shared `t_context` structure.

A separate `logger` module provides the `ft_log` function, which is the only allowed entry point for printing simulation events.

Each log operation is protected by a mutex lock to ensure that:

- messages from different threads do not interleave;
- output remains deterministic and readable;
- race conditions on stdout are eliminated;
- logs reflect a consistent timeline of events.

This design guarantees thread-safe logging without requiring coders to manage synchronization explicitly. All logging coordination is centralized in the `logger` module and enforced globally via the shared context mutex.

## Thread synchronization mechanisms

The project uses POSIX threads (`pthread`) combined with mutexes and condition variables to coordinate concurrent execution between coders, the scheduler, and the monitor.

The synchronization model is built around shared state (`t_context`), protected resources (dongles), and controlled execution flow (scheduler + condition variables).

---
## Global context synchronization

All shared simulation data is stored inside the central `t_context` structure:

- coder array
- dongle array
- simulation state (`is_running`)
- start timestamp
- scheduler thread
- monitor thread

A global mutex (`state_mutex`) protects access to shared simulation state such as:
- `is_running` flag
- shared lifecycle updates

This ensures consistent system-wide state visibility across all threads.

---
## Dongle synchronization

Each dongle is protected by its own `pthread_mutex_t` (`dongle_mutex`).

### Deadlock prevention

Deadlocks are prevented by enforcing a strict global ordering when locking dongles:

```c
if (d1 < d2)
    lock(d1) -> lock(d2)
else
    lock(d2) -> lock(d1)
```
This guarantees:
 - no circular wait condition
 - no inconsistent locking order between threads
A helper function (`ft_lock_pair`) enforces this rule for all coders.

### Queue-based resource scheduling
Each dongle maintains a request queue representing pending execution requests.
Synchronization rules:
 - requests are added under mutex protection
 - requests are removed only by the scheduler

queue access is always protected by dongle mutex

This ensures:
 - fair access to shared dongles
 - no race conditions between coders competing for resources


### Condition variable synchronization
Coders do not execute immediately after acquiring resources.
Instead, they wait for scheduler approval using a condition variable:
```c
pthread_cond_wait(&coder->cond, &coder->mutex);
```

The scheduler wakes coders when:
 - their request is valid
 - both dongles are available
 - cooldown conditions are satisfied

This prevents busy waiting and enables controlled execution flow.

### Monitor synchronization
A dedicated monitor thread supervises the lifecycle of all coders.
It safely reads shared state under mutex protection and performs:
 - Burnout detection
 - If a coder exceeds its deadline without compiling, the monitor:
 - logs the event
 - stops the simulation `(is_running = false)`
 - Completion detection

The monitor checks if all coders reached the required number of compiles.
If so, it gracefully terminates the simulation.
The monitor ensures centralized and deterministic system termination.

### Scheduler synchronization
The scheduler thread is responsible for granting execution permission.
It:
 - locks both dongles before inspecting queues
 - checks if a coder is ready (`ft_is_ready`)
 - validates cooldown constraints
 - grants execution permission via condition variable signaling

This ensures controlled and conflict-free execution ordering.

# Instructions
## Compilation
To build the project run:
```
make
```
To run executable:
```
./codexion --coders <number_of_coders> --burnout <time_to_burnout> --compile <time_to_compile> --debug <time_to_debug> --refactor <time_to_refactor> --dongle <dongle_cooldown> --compiles <compiles> --scheduler <scheduler_algorithm: "edf" | "fifo">
```
example:
```
./codexion --coders 4 --burnout 1000 --compile 200 \
               --debug 100 --refactor 100 --dongle 200 \
               --compiles 3 --scheduler edf
```
You can also use the provided Makefile rule:
```
make run
```
## Cleaning build files
Remove object files:
```
make clean
```
Remove object files and executable:
```
make fclean
```
Rebuild the entire project
```
make re
```

# Resources

## Classic references

This project is based on standard concepts of concurrent programming, thread synchronization, and shared resource management. The following materials were used for understanding and implementing the system:

- POSIX Threads (pthreads) documentation  
  https://man7.org/linux/man-pages/man7/pthreads.7.html  

- pthread functions manual pages  
  https://man7.org/linux/man-pages/man3/pthread_create.3.html  
  https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html  
  https://man7.org/linux/man-pages/man3/pthread_mutex_init.3.html  

- Operating Systems: Three Easy Pieces (OSTEP) — Concurrency  
  https://pages.cs.wisc.edu/~remzi/OSTEP/  

- Dining Philosophers Problem (classic concurrency model)  
  https://en.wikipedia.org/wiki/Dining_philosophers_problem  

- Scheduling algorithms (EDF, FIFO)  
  https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling  
  https://en.wikipedia.org/wiki/Scheduling_(computing)  

- Time management in C (`gettimeofday`)  
  https://man7.org/linux/man-pages/man2/clock_gettime.2.html  

---

## AI Usage Description

AI assistance (Gemini) was used during the development of this project as a support tool for explanation, structuring, and documentation.

### Concept understanding
- Explaining concurrency concepts such as:
  - race conditions
  - deadlocks
  - starvation
  - mutual exclusion

---

AI was used strictly as an **assistive tool for learning, explanation, and documentation**, while all implementation and final design decisions were made by the author of the project.
