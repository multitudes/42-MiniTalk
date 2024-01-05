# 42-MiniTalk (In progress)
The purpose of this project for 42Berlin is to code a small data exchange program using UNIX signals. (Version: 3)

## The rules
We have to turn in a Makefile.  
We have to handle errors thoroughly. In no way your program should quit unex-
pectedly (segmentation fault, bus error, double free, and so forth).
Our program mustn’t have memory leaks.  
We can have one global variable per program (one for the client and one for
the server), but we will have to justify their use.


### Allowed functions
In order to complete the mandatory part, we are allowed to use the following
functions:
◦ write  
◦ ft_printf and any equivalent we coded  
◦ signal  
◦ sigemptyset  
◦ sigaddset  
◦ sigaction  
◦ kill  
◦ getpid  
◦ malloc  
◦ free  
◦ pause  
◦ sleep  
◦ usleep  
◦ exit  

## Mandatory Part
We must create a communication program in the form of a client and a server.  
The server must be started first. After its launch, it has to print its PID.  
The client takes two parameters:  
◦ The server PID.  
◦ The string to send.  

The client must send the string passed as a parameter to the server.
Once the string has been received, the server must print it.  
The server has to display the string pretty quickly. Quickly means that if you think
it takes too long, then it is probably too long.

Our server should be able to receive strings from several clients in a row without
needing to restart. The communication between the client and the server has to be done only using
UNIX signals.  We can only use these two signals: SIGUSR1 and SIGUSR2.  

## Bonus part
The server acknowledges every message received by sending back a signal to the
client. Unicode characters support!

## Signals and IPC
In Linux, signals are a form of inter-process communication (IPC) used to notify a process that a specific event has occurred. Processes can send signals to other processes, and a process can define how it responds to different signals. Two common signals used for communication between processes are `SIGUSR1` and `SIGUSR2`, which stand for "User-defined signal 1" and "User-defined signal 2," respectively.

Here's a basic example of two programs communicating with each other using `SIGUSR1` and `SIGUSR2`:

### Program 1

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        printf("Received SIGUSR1 signal.\n");
    } else if (signo == SIGUSR2) {
        printf("Received SIGUSR2 signal.\n");
    }
}

int main() {
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    // Infinite loop to keep the program running
    while (1) {
        sleep(1);
    }

    return 0;
}
```

### Program 2

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

pid_t target_pid;  // Global variable to store the target process ID

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        printf("Sender process received SIGUSR1 signal.\n");
    } else if (signo == SIGUSR2) {
        printf("Sender process received SIGUSR2 signal.\n");
    }
}

int main() {
    // Get the process ID of the target process (Program 1)
    target_pid = /* Replace this with the actual PID of Program 1 */;

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    // Infinite loop to keep the program running
    while (1) {
        // Send SIGUSR1 signal to the target process
        kill(target_pid, SIGUSR1);
        sleep(2);

        // Send SIGUSR2 signal to the target process
        kill(target_pid, SIGUSR2);
        sleep(2);
    }

    return 0;
}
```

You can obtain the PID of Program 1 by running it and checking the process ID using tools like `ps` or `pgrep`.  
In this example, the program 1 registers signal handlers for `SIGUSR1` and `SIGUSR2`. The program 2 sends these signals to the other process using the `kill` system call. The Sender process, upon receiving the signals, executes the corresponding signal handler functions.

There are also more advanced IPC mechanisms available for inter-process communication, such as pipes, sockets, and message queues.

## SIGUSR1 & SIGUSR2
SIGUSR1 and SIGUSR2 are available for programmer-defined purposes. The kernel never generates these signals for a process. Processes may use these signals to notify one another of events or to synchronize with each other. In early UNIX implementations, these were the only two signals that could be freely used in applications. (In fact, processes can send one another any signal, but this has the potential for confusion if the kernel also generates one of the signals for a process.) Modern UNIX implemen- tations provide a large set of realtime signals that are also available for programmer-defined purposes 

## The header signal.h on mac?
```
locate signal.h
```