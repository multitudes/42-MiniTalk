/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:25 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 16:30:41 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	_decoder(char *byte)
{
	int	i;
	int	dec;
(void)byte;
	i = 0;
	dec = 65;
	while (i < 8)
	{
		// dec = dec * 2 + byte[i] - '0';
		i++;
	}
	return (dec);
}

void	sighandler(int sig, siginfo_t *siginfo, void *ucontext)
{
	char byte[9];
	(void)ucontext;
	static int bits = 0;

	if (sig == SIGUSR1) {
		byte[bits] = '1';
		bits++;
		//  printf("SIGUSR1!! %d\n", bits);
		//write(1,"bits\n",6);
	} 
	else if (sig == SIGUSR2)
	{
		byte[bits] = '0';
		bits++;
		// printf("SIGUSR2!! %d\n", usr2);
		//write(1,"usr2\n",6);
	}
	if (bits == 8)
	{
		byte[8] = 0;
		bits = 0;
		printf("si pid %d - %s\n", siginfo->si_pid, byte);
		printf("%c",_decoder(byte));
		kill(siginfo->si_pid,SIGUSR1);
	}

	// if (sig == SIGUSR1) {
	// 	byte[bits++] = '1';
	// 	//  printf("SIGUSR1!! %d\n", bits);
	// 	write(1,"usr1\n",6);
	// } 
	// else if (sig == SIGUSR2)
	// {
	// 	byte[bits++] = '0';
	// 	// printf("SIGUSR2!! %d\n", usr2);
	// 	write(1,"usr2\n",6);
	// }
	// if (bits == 7)
	// {
	// 	bits = 0;
	// 	byte[8] = 0;	
	// 	printf("si pid %d and byte %c\n", siginfo->si_pid, 65 );
	// 	// kill(siginfo->si_pid,SIGUSR1);// _decoder(byte)
	// }
	// kill(siginfo->si_pid,SIGUSR1);
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