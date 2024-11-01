# notes about my final code 
my output processes are all the same numbers and the pid is always zero 
and i have an odd error for panic: sched ptable.lock

# Part 4

## Questions from Part 3

### (a) What happens when a process returns from I/O in terms of state transition?

Answer: The I/O becomes available and the state transitions from blocked to ready

### (b) What does void sched(void) do?

Answer: checks for fatal errors and if it finds one it will trigger kernel panic and then it will switch to scheduler and update the cpu's itena value

### (c) How does the scheduler select a process for running? (See void scheduler(void))

Answer: the scheduler loops through the ptable looking for the first runnable process and calls switchuvm to switch to that process, then returns to the scheduler to set the next process immediately after it to run. the scheduler runs in the order of first runnable process    

### (d) What happens when a process is created? (See static struct proc *allocproc(void))

Answer: alloc proc function scans through the ptable looking for any unused process and then uses that empty
space to make a new process. it sets the new proccess state to EMBRYO and sets it to run in the kernel
. the new process' pid is set and allcoated to the kernel stack, created space for the trapfra, new context, 
and initalizes the time stats to zero except for creation time being set to the current tick in seconds

## Questions from Part 4

### Q2 What is a major difference between threads and processes?

Answer: A process is a running program in a computer system, whereas a thread is one sequence of tasks withing a process. Processes is a large execution and can be therefore split into lightweight process which are threads, since processes run in separate memory spaces and threads share address space multiple threads can run at the same time. 

### Q3 Explain how the shell uses fork() and exec() to execute an arbitrary command

Answer: fork() creates an indentical child of the current but still preserves the original process whereas the exec() replaces the current process with another process. 
In order to execute an arbitrary command the shell will first execute fork() copying the current process creating a child process and then execute exec() to replace the old process wiht the newly created child process to run the arbitrary command until the child process fineshes completely with exit(). Then finally the original process can resume its execution 

### Q4 Briefly explain how the OS switches between processes.

Answer: In order for the OS  to run multiple proccess on a CPU at a time it switches between processes through schedulers that manage processes what proccesses will be ran and for how long. schedulers use states such as new, ready, blocked, running, and terminated to assign to procees to indicate their current status in order to give priority to procces in execution