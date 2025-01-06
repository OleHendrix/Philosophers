# Philosophers  

Philosophers is a multithreading project written in C that simulates the classic "Dining Philosophers Problem." The goal is to manage the synchronization and resource sharing between multiple philosophers to avoid deadlocks and starvation while ensuring accurate timing.

## How It Works  

1. **The Dining Philosophers Problem**  
   - A group of philosophers sits at a round table with a fork between each pair of philosophers.  
   - Each philosopher alternates between eating, thinking, and sleeping.  
   - To eat, a philosopher must pick up the two forks adjacent to them (one at a time).  

2. **Simulation Mechanics**  
   - Each philosopher is represented by a thread to simulate concurrent behavior.  
   - Shared resources (forks) are managed using mutexes to ensure proper synchronization.  

3. **Challenges Addressed**  
   - **Deadlock Prevention**: Careful design ensures that philosophers do not end up in a state where they are all waiting indefinitely for forks.  
   - **Starvation Avoidance**: Philosophers eventually get to eat without being perpetually blocked by others.  
   - **Precise Timing**: Timing for eating, sleeping, and thinking is accurately simulated using system calls (`gettimeofday`) to manage delays.  

4. **Input Parameters**  
   - The program accepts the following arguments:  
     - Number of philosophers.  
     - Time to die: Maximum time a philosopher can go without eating.  
     - Time to eat: Duration a philosopher spends eating.  
     - Time to sleep: Duration a philosopher spends sleeping.  
     - (Optional) Number of times each philosopher must eat.  

5. **Error Handling**  
   - Validates input to ensure all parameters are correct and within acceptable ranges.  
   - Handles thread creation and resource allocation errors gracefully.  

## What I Learned  
- The fundamentals of multithreading using `pthread` in C.  
- How to use mutexes to synchronize access to shared resources and prevent race conditions.  
- Techniques for solving concurrency challenges like deadlocks and starvation.  
- Managing precise timing and delays in a multithreaded environment.  
- Writing efficient and scalable code for concurrent systems.  
