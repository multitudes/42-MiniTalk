# 42-MiniTalk

> If you find that you’re spending almost all your time on theory, start turning some attention to practical things; it will improve your theories. If you find that you’re spending almost all your time on practice, start turning some attention to theoretical things; it will improve your practice. — Donald Knuth

The purpose of this project for 42Berlin is to code a small data exchange program using only the UNIX signals. (Version: 3)  it is thought as a challenge, in the real world signals will not be used in this way to communicate between processes, since they are mostly used by the kernel, but in this way we learn to think and handle signals.  

## The rules
We have to turn in a Makefile.  
We have to handle errors thoroughly. In no way our program should quit unexpectedly 
(segmentation fault, bus error, double free, and so forth).
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

## The code
Here's a basic example of two programs communicating with each other using `SIGUSR1` and `SIGUSR2`.  

Each signal is defined as a unique (small) integer, starting sequentially from 1. These integers are defined in <signal.h> with symbolic names of the form SIGxxxx.

When the process receives a signal, he can either ignore it, terminate or block it and react later. Also upon receiving a signal we could launch a handler to do some cleaning before quitting for example. When we change the default behaviour for a signal, this is also called changing the disposition of a signal. There are a few ways to do that.  There are a few ways of changing the disposition of a signal.  

The first, signal(), is prototyped like this, with the handler which is a pointer to a function:   
```c
#include <signal.h>
void (*signal(int sig, void (*handler)(int)))(int);
```
or with a typedef making it easier to read:
```c
typedef void (*sig_t) (int);

sig_t
signal(int sig, sig_t func);
```
The second argument is the handler to be called when the signal arrives:
```c
void    handler(int sig)
{
    /* Code for the handler */
}
```
From the man pages:  
>  This signal() facility is a simplified interface to the more general sigaction(2) facility.

Example of soft exit sending a ^C (interrupt signal or SIGINT) to a process.  
```c
/* change the disposition with signal() and add the handler, check that it has not failed */
if (signal(SIGINT, exit_handler) == SIG_ERR)
    return (_exit_err("signal failed\n"));
```
The handler
```c
void	exit_handler(int sig)
{
	(void)sig;
	write(1,"\n== bye bye! ==\n",9);
	exit(0);
}
```

### Program 1 - the server

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

void	exit_handler(int sig)
{
	(void)sig;
	write(1,"\n== bye bye! ==\n",9);
	exit(0);
}

int main() {
    signal(SIGUSR1, signal_handler); /* add checks */
    signal(SIGUSR2, signal_handler); /* add checks */
    
    /* with checks */
    if (signal(SIGINT, exit_handler) == SIG_ERR)
		return (_exit_err("signal failed\n"));


    // Infinite loop to keep the program running
    while (1) {
        sleep(); // sleep will save CPU cycles since the process is blocked here until a signal is received
    }
    return 0;
}
```

Launching it will give :

```
$> ./server
server pid 22473 
^C
== bye bye ==
$>     
```

Example of initializing the signal handlers for the server. I consider the 5 signals corresponding to keyboard interrupt which could be being entered by a user. Typically the ^C, ^\, ^D, ^Z, ^HUP, ^ABRT. I will add the handler for each of them.  Other signals are sent by the kernel to the process like SIGKILL and will not need to handle them.  
```c
if ((signal(SIGQUIT, exit_handler) == SIG_ERR) || \
	(signal(SIGINT, exit_handler) == SIG_ERR) || \
	(signal(SIGTERM, exit_handler) == SIG_ERR) || \
	(signal(SIGHUP, exit_handler) == SIG_ERR) || \
	(signal(SIGABRT, exit_handler) == SIG_ERR))
	return (_exit_err("SIG_ERR signal failed\n"));
```

### Program 2 - the client

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        printf("Sender process received SIGUSR1 signal.\n");
    } else if (signo == SIGUSR2) {
        printf("Sender process received SIGUSR2 signal.\n");
    }
}

int main(int argc, char *argv[]) {
    // Get the process ID of the target process and pass it as arg with the message
	if (!(argc == 3) || !_getint(argv[1]) || argv[1] == NULL)
		return (_exit_err("Usage ./client pid message\n"));
    target_pid = _getint(argv[1]); /* _getint is an utility func */

    // register the signal handler. In this case I only need the SIGUSR1 which will be the acknoledgement from the server
    if (signal(SIGUSR1, signal_handler) == SIG_ERR)
        /* exit code here */;


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

There are also more advanced IPC mechanisms available for inter-process communication, such as pipes, sockets, and message queues but in this project the challenge is to use only the SIGUSR1 and SIGUSR2.

## SIGUSR1 & SIGUSR2
SIGUSR1 and SIGUSR2 are available for programmer-defined purposes. The kernel never generates these signals for a process. Processes may use these signals to notify one another of events or to synchronize with each other. In early UNIX implementations, these were the only two signals that could be freely used in applications. (In fact, processes can send one another any signal, but this has the potential for confusion if the kernel also generates one of the signals for a process.) Modern UNIX implemen- tations provide a large set of realtime signals that are also available for programmer-defined purposes 

## CTRL-Z

This is a signal as well. 
When you press `Ctrl-Z` in the Linux command line, you are sending the foreground process to the background and suspending it. The shell displays a message indicating that the process has been suspended.

To bring the suspended process back to the foreground, you can use the `fg` command (foreground). In your case, it would look like this:

```bash
fg
```

This will resume the execution of the process and bring it back to the foreground. If you have multiple suspended processes, you can specify the job number to bring a specific one to the foreground:

```bash
fg %1  # Replace 1 with the job number of your process
```

If you want the process to continue running in the background, you can use the `bg` command (background) instead of `fg`:

```bash
bg
```

This will resume the execution of the process in the background. If you have multiple suspended processes, you can specify the job number for `bg` as well:

```bash
bg %1  # Replace 1 with the job number of your process
```

These commands work with the job control feature in Unix-like operating systems, allowing you to manage processes in the foreground and background within the same shell session.
# Unicode
Definitely one of the most interesting aspects of this project has been delving deeper into Unicode. What an increadible and underrated standard for displaying characters in multiple scripts and idioms including emoji and majong tiles!
I realized that I did not need to add any special support. Sending an emoji is interpreted and decoded automatically in the shell terminal. 

## variants of UNICODE 
Unicode is a character encoding standard that aims to represent every character from every writing system in use today. Different Unicode Transformation Formats (UTF) are used to encode these characters for storage and processing. Here are the main UTF variants:

1. **UTF-8:**
   - UTF-8 is the most widely used Unicode encoding. It represents each character in one to four bytes, with ASCII characters using one byte and extended characters using more.
   - It's backward compatible with ASCII, meaning that ASCII-encoded text is also valid UTF-8.

2. **UTF-16:**
   - UTF-16 uses two bytes (16 bits) to represent most characters but uses a pair of two-byte sequences, known as a surrogate pair, to represent characters beyond the Basic Multilingual Plane (BMP).
   - It is commonly used in environments where characters outside the BMP are rare.

3. **UTF-32:**
   - UTF-32 uses four bytes (32 bits) to represent each character. Each character is represented by a fixed-size 32-bit unit.
   - It is less commonly used than UTF-8 and UTF-16 due to its larger storage requirements.

4. **UTF-7:**
   - UTF-7 is a variable-width encoding that represents characters using seven bits per base character. It is used in email protocols and has limited usage outside of that context.

5. **UTF-EBCDIC:**
   - UTF-EBCDIC is an encoding used on IBM mainframes. It is similar to UTF-16 but uses the EBCDIC character set.

Among these, UTF-8 is often preferred for text encoding in many applications due to its efficiency, compatibility with ASCII, and widespread adoption on the internet.

It's important to note that the terms "UTF" and "Unicode" are sometimes used interchangeably, but they refer to different concepts. Unicode is a character set, while UTF is a set of character encoding schemes that allow the representation of Unicode characters.

## The way UTF-8 works 
For example since it is still compatible with ascii, which in its basic form needs 7 bits. (See the man ascii mage for the values from 0 to 127.) When encoding a a char it will be using 1 byte. But when using the 🥰 emoji it will use 4 bytes (32 bits). How does this work? Lets examine the 4 bytes in the emoji encoding as I send them to the serveer:  
11110000 10011111 10100101 10110000 00000000  
The last byte is all zeroes. This is my end of string '\0' null terminator.  
I have 4 bytes.  
11110000 10011111 10100101 10110000  

Let's evaluate the binary sequence `11110000100111111010010110110000`:

- First byte: `11110000` (4 bits of data)
- Second byte: `10011111` (6 bits of data)
- Third byte: `10100101` (6 bits of data)
- Fourth byte: `10110000` (5 bits of data)

Concatenating all the bits together:

```
11110000 10011111 10100101 10110000
   11110000100111111010010110110000
```

Now, the correct binary `11110000100111111010010110110000` corresponds to the Unicode code point represented by this UTF-8 sequence.

## a breakdown
in a UTF-8 encoded Unicode sequence, the first few bits of the first byte indicate the total number of bytes used to represent the character. UTF-8 is a variable-width encoding, meaning that different characters may use different numbers of bytes. The leading bits of the first byte help determine the length of the encoded sequence.

Here's a breakdown of the structure of a UTF-8 encoded sequence:

- If the first byte starts with `0`, it represents a single-byte character (ASCII character) and is followed by 7 bits of character data.
- If the first byte starts with `110`, it represents a two-byte character and is followed by a total of 11 bits of character data spread across the first and second bytes.
- If the first byte starts with `1110`, it represents a three-byte character and is followed by a total of 16 bits of character data spread across the first, second, and third bytes.
- If the first byte starts with `11110`, it represents a four-byte character and is followed by a total of 21 bits of character data spread across the first, second, third, and fourth bytes.

The remaining bytes in a multi-byte sequence start with `10` followed by 6 bits of character data.

## Unicode Code points
In Unicode, characters can be represented using their hexadecimal code points. The code point for the "🥰" emoji is U+1F970. When you enter <0001f970> in some contexts, the system might interpret it as a Unicode escape sequence or code point, leading to the display of the corresponding emoji.

### last tweaks
To prevent terminal input from being displayed on the command line while my server program is running, I can consider putting the terminal in raw mode to disable line buffering and echo. This way, input characters won't be displayed on the terminal.  
This has functions which are not allowed in the subject therefore I will leave it here.  

Here's a simple example in C using termios to put the terminal in raw mode:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

void setRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main() {
    setRawMode();

    while (1) {
        // Your main program logic here
        // Example: processing signals and performing tasks

        // For demonstration purposes, let's break out of the loop after a while
        usleep(500000);  // Sleep for 0.5 seconds
        break;
    }

    // Restore terminal to normal mode before exiting
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    printf("Exiting...\n");
    return 0;
}
```

In this example:

- The `setRawMode` function modifies the terminal settings to disable echoing (`ECHO`) and canonical mode (`ICANON`), effectively putting the terminal in raw mode.
- The `main` function enters a loop where you can perform your main program logic.
- To illustrate, a `usleep` is used to simulate a running program for demonstration purposes. Replace this with your actual program logic.
- Before exiting, the terminal settings are restored to normal mode to ensure proper cleanup.

Remember that this approach may affect the way your program interacts with terminal input, so it's important to handle input processing appropriately based on your requirements.

### The header signal.h on mac?
I was looking for the signal.h header file on my mac. There is the command locate for that. Turns out that there are many versions of this file on my system depending of where it is used! Interesting...
```
locate signal.h
```

## LINKS:
[Recommended book: Kerrisk - The Linux Programming Interface](https://man7.org/tlpi/)  
[Testing with Lorem Ipsum](http://loremipsum360.com)  

