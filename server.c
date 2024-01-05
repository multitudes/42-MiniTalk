/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:25 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 14:18:05 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

// static int usr1 = 0;
// static int usr2 = 0;
typedef void (*sighandler_t)(int);


void	sighandler(int sig, siginfo_t *siginfo, void *ucontext)
{
	(void)ucontext;
	static int usr1 = 0;
	if (usr1 == 1)
	{
		printf("si pid %d\n", siginfo->si_pid);
		kill(siginfo->si_pid,SIGUSR1);
	}
	if (sig == SIGUSR1) {
		usr1++;
		 printf("SIGUSR1!! %d\n", usr1);
		write(1,"usr1\n",6);
	} 
	else if (sig == SIGUSR2)
	{
		// usr2++;
		// printf("SIGUSR2!! %d\n", usr2);
		write(1,"usr2\n",6);
	}
}

void	exit_handler(int sig)
{
	(void)sig;
	write(1,"\n== bye bye! ==\n",17);
	exit(0);
}

int	exit_err(char *msg)
{
	printf("%s\n",msg);
	return (1);
}

int	main(void)
{
	pid_t pid;
  	struct sigaction act;

	pid = getpid();
	printf("server pid %d \n",pid);
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_sigaction = sighandler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
			return (exit_err("sigaction server failed\n"));
	if (sigaction(SIGUSR2, &act, NULL) == -1)
			return (exit_err("sigaction failed\n"));
	if (signal(SIGINT, exit_handler) == SIG_ERR)
		return (exit_err("signal failed\n"));
	while (1)
		pause();
	return (0);
}