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
# Instructions

# Resources
- [article about the project](https://dev.to/yel-bakk/codexion-4fk8) 
- [github repo for the project](https://github.com/ahmad-nashwan/Philosophers)
- [another github repo for the project](https://github.com/DeRuina/philosophers/tree/main/src)
- [difference between concurrent and parallel programming](https://www.geeksforgeeks.org/operating-systems/difference-between-concurrency-and-parallelism/)
- [threads and why theyre needed](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)
