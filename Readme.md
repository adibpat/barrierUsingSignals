/* Single Author Info:
*  abpatwar Aditya B Patwardhan
*/

Introduction:
-------------
The synchronization primitive 'barrier' has been implemented using UNIX signals.

Files provided in the implementation:
-> mybarrier.h
-> mybarrier.c


mybarrier.c contains the following methods:
-> mybarrier_init()
-> mybarrier_wait()
-> mybarrier_destroy()


Barrier:
--------
The barrier provides mechanism to block all threads till all threads reach the barrier.
When all threads reach the barrier, the threads are unblocked.


Implementation details:
----------------------




Test Case:
----------
A test file test.c tests the implementation of the barrier.

The program tests 10 threads over 2 barriers.
Each thread adds it's own thread number into an array and then waits at the barrier.
Once all the threads have reached the barrier, the threads proceed to calculate the sum of the elements in the array.
If sum = 45 (sum of all numbers from 0 to 9), then all the threads have successfully passed through the barrier and the barrier test is passed.


How to Build:
------------
The Makefile provides a bunch of targets; each one builds a particular part of the project.

Refer to the following commands for building ->
Compiling:
     $ make
# This is equivalent to "make all".
# It compiles all the code files, creates the corresponding object files. 
# It also builds the test.c file - a sample test program provided - which tests out the methods in mybarrier.c.

Cleaning:
     $ make clean

Test file:
     $ make test
