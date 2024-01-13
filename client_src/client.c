/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:36 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/13 17:36:21 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/* 
I need a static variable because there is no way of passing this info 
which I get from the command line args, to the handler of a signal. 
It has to be global.
*/
pid_t	g_pid;

/*
my client will wait until he gets the ack from server and then it 
terminates - this handler listens to SIGUSR1 only and checks that 
the pid is correct before terminating.
*/
static void	ack_handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	char	*server_pid_str;

	(void)sig;
	(void)ucontext;
	if (siginfo->si_pid == g_pid)
	{
		server_pid_str = ft_itoa(g_pid);
		write(1, "\n===== Server pid ", 19);
		write(1, server_pid_str, ft_strlen(server_pid_str));
		write(1, " - ACK msg received ====== \n", 29);
		free(server_pid_str);
		exit(0);
	}
}

/*
Just to exit gracefully in case of SIGINT SIGQUIT etc
*/
static void	exit_handler(int sig)
{
	(void)sig;
	write(1, "\n== bye bye! ==\n", 17);
	exit(0);
}

/*
*** CLIENT ***
I get the command line args first. The _getint will get the first
which is the server pid and check if it is a number and if it can be 
reachable with the check kill(g_pid, 0) 
If I do not have a second arg then I print usage.
I have the exit_handler even if it is 
unlikely that when I send a message I would have the time to 
send a SIGINT or SIGQUIT...
Then I initialize my sigaction mask as in the server to get the 
acknowledgment back of my message - here I can also get the
pid of the server. A bit overkill but why not. 
I wait for the ack from the server and if I dont get it 
I would need to manually shut down.
*/
int	main(int argc, char *argv[])
{
	struct sigaction	act;

	g_pid = _getint(argv[1]);
	if (!(g_pid) || kill(g_pid, 0) != 0)
		return (_exit_err("pid error\n"));
	if (!(argc == 3))
		return (_exit_err("Usage ./client pid message\n"));
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = ack_handler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return (_exit_err("sigaction client failed\n"));
	if (signal(SIGINT, exit_handler) == SIG_ERR || \
		(signal(SIGQUIT, exit_handler) == SIG_ERR) || \
		(signal(SIGTERM, exit_handler) == SIG_ERR) || \
		(signal(SIGHUP, exit_handler) == SIG_ERR) || \
		(signal(SIGABRT, exit_handler) == SIG_ERR))
		return (_exit_err("signal failed\n"));
	if (!_send_str(argv[2]))
		return (_exit_err("\nFailed to send string\n"));
	while (1)
		pause();
	return (0);
}
