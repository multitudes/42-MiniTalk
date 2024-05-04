/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:25 by lbrusa            #+#    #+#             */
/*   Updated: 2024/05/02 18:29:05 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	exit_handler(int sig)
{
	(void)sig;
	write(1, "\n== bye bye! ==\n", 17);
	exit(0);
}

/*
I use static functions for the handlers because they are only 
for the server to use.
the signature of sighandler is required. ucontext is not usually used.
siginfo_t contains the pid of the sender.
sig is the signal received. 
*/
static void	sighandler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static char		byte[9];
	char		c;
	static int	bits = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		byte[bits++] = '1';
	else if (sig == SIGUSR2)
		byte[bits++] = '0';
	if (bits == 8)
	{
		byte[8] = 0;
		bits = 0;
		c = _decoder(byte);
		write(1, &c, 1);
		if (!c)
			if (kill(siginfo->si_pid, SIGUSR1) != 0)
				write(1, "\nCould not send ack to client si_pid error\n", 44);
	}
}

/*
*** server ***
It is a simple program which will first print its pid.
Then will initialise the sigaction struct with the 
sigemptyset func (required)
SA_SIGINFO is passed as flags, this is to make possible to pass
some info about the sender to the handler (notably its pid)
I associate my sighandler to SIGUSR1 and SIGUSR2
and the exit handler to SIGINT which is contr-c
Then I loop and pause. looping without pausing would make my 
m1 mac overheat with a CPU of 100% so it is an important detail.
I can exit (gracefully with SIGINT and other like ).
SIGTERM can be generated by kill -15 <process_id>
SIGHUP with kill -1 <process_id>
Once one of the other signals is received

*/
int	main(void)
{
	struct sigaction	act;

	_print_pid();
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = sighandler;
	act.sa_flags = SA_SIGINFO;
	if ((sigaction(SIGUSR1, &act, NULL) == -1) || \
		(sigaction(SIGUSR2, &act, NULL) == -1) || \
		(signal(SIGQUIT, exit_handler) == SIG_ERR) || \
		(signal(SIGINT, exit_handler) == SIG_ERR) || \
		(signal(SIGTERM, exit_handler) == SIG_ERR) || \
		(signal(SIGHUP, exit_handler) == SIG_ERR) || \
		(signal(SIGABRT, exit_handler) == SIG_ERR))
		return (_exit_err("SIG_ERR signal failed\n"));
	while (1)
		pause();
	return (0);
}
