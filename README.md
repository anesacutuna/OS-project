
# Our Project

Implementation of a Shell in C program.



## Project Members
Anesa Cutuna
Alem Borcak
## Files
shell.c

## Questions
Q1: If we have a single-core, uniprocessor system that supports multiprogramming, how many
processes can be in a running state in such a system, at any given time?
Answer is one.

Q2: Explain why system calls are needed for a shared memory method of inter-process
communication (IPC). If there are multiple threads in one process, are the system calls needed
for sharing memory between those threads?
Answer: They're required since each process has its own address space, and the kernel must be involved when dealing with the address space of other processes. Because the kernel (rather than the process) is aware of all processes' physical memory mappings, it can choose a memory chunk that can be shared by several processes.
Because threads share their address space by definition, they don't need to make a system call to share memory

## Outline of the Assignment
We created a clear and effective presentation of the c shell commands needed for the assignment. The majority of commands are separated into distinct functions, each with a name that corresponds to the command's capability.

## Instructions for compiling
gcc shell.c -o shell   
./shell

## Challenges
Finding suitable resources, obtaining the input 2nd and 3rd parameters, studying and discovering examples of csh commnads in use, and determining how to apply them were all problems we had while working on this endeavor.
## Sources
https://www.geeksforgeeks.org/making-linux-shell-c/

https://www.w3schools.com/whatis/whatis_cli.asp

https://brennan.io/2015/01/16/write-a-shell-in-c/

https://www.programiz.com/c-programming/c-file-input-output

https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e

https://www.youtube.com/watch?v=spD11nnLsLE

https://www.youtube.com/watch?v=cNBrsrvxeQg
