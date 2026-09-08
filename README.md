*This activity has been created as part of the 42 curriculum by nalayyou*

# Description
  this activity is a simulation of the [dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem) with some changes to it. 

  Visual Representation 

  ![alt_text](./images/philosophers.jpg)
  
  coders (representing philosophers) alternatively compile, debug, or refactor.
- While compiling, they are not debugging nor refactoring;
- while debugging, they are not compiling nor refactoring;
- and, of course, while refactoring, they are not compiling nor debugging.

  there are as many dongles (forks) as coders. a coder needs their left and right dongles to compile.
  when a coder is done compiling they put both dongles back and starting debugging. 

  when a coder is done debugging, they start refactoring.

  The simulation stops when a coder burns out due to lack of compiling.

  ## Important concepts to understand before starting the project
    -  concurrent programming : managing multiple tasks at once. on a single core CPU the processor will quickly switch between tasks. tasks are in execution during the same time period but only one is actively executed at any given instant.
 
    -  parallelism : is executing multiple tasks at the exact same time. this is only possible with a multiple core CPU.
    
    - process vs thread : a process consists of one or more threads. a process is a management concept , resources are allocated to a process and not a thread. all threads belonging to the same process get access to the same resources.
    
    - mutex : stands for mutually exclusive flag/object which is self explanatory. a flag is mutual between threads but is exclusive to one at a time.
    
    - lockout freedom : a concept linked to mutex, it guarantees that every thread that wishes to enter the critical section will do so eventually. no process remains in critical section permanently.
 
    - race condition : it occurs when two or more processes or threads try to access and/or modify data at the same time. the result is determined by which one was milliseconds faster.
 
    - user level threads vs kernel level threads : in short user level threads (green threads) are managed by your language and cant take advantage of parallelism [for more info](https://stackoverflow.com/questions/15983872/difference-between-user-level-and-kernel-supported-threads))\

  ## getting started with pthread library
    - creating a thread
      ```
      pthread_create( address of empty pthread_t variable, struct for attributes of thread, function that the thread will run, one piece of data that you want to pass to previous said function)
      example
      pthread_t t;
      pthread_create(&t, NULL, say_hello, NULL);
      ```
    - waiting for a thread to finish
      ```
      pthread_join(t, NULL);
      ```
    - terminating the calling thread explicitly
      ```
      pthread_exit(NULL);
      ```
      
# Instructions

# Resources
- [article about the project](https://dev.to/yel-bakk/codexion-4fk8) 
- [github repo for the project](https://github.com/ahmad-nashwan/Philosophers)
- [another github repo for the project](https://github.com/DeRuina/philosophers/tree/main/src)
- [difference between concurrent and parallel programming](https://www.geeksforgeeks.org/operating-systems/difference-between-concurrency-and-parallelism/)
- [threads and why theyre needed](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)
- [difference between fork and clone](https://stackoverflow.com/questions/4856255/the-difference-between-fork-vfork-exec-and-clone)
- [process vs thread](https://www.reddit.com/r/explainlikeimfive/comments/k1ig1e/eli5_the_difference_between_a_process_and_a_thread/)
- [process vs thread more in depth](https://algomaster.io/learn/concurrency-interview/processes-vs-threads)
- [what is mutual exclusion](https://en.wikipedia.org/wiki/Mutual_exclusion)
- man page
