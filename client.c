/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:36 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 16:28:30 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
 
//  /* Print list of signals within a signal set */
// void printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
// {
// int sig, cnt;
// cnt = 0;
// for (sig = 1; sig < NSIG; sig++) {
// 	if (sigismember(sigset, sig)) { cnt++;
// 		fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig)); }
// }
// if (cnt == 0)
// 	fprintf(of, "%s<empty signal set>\n", prefix);
// }

/* 
I need it because there is no way of passing this info which I get
from the arguments of my client process to the handler of a signal. 
It has to be global
*/
static pid_t pid;

int	_getint(const char *str)
{
	int	n;
	int	sign;

	if (str == NULL)
		return (0);
	n = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	while ((*str <= '9' && *str >= '0'))
		n = 10 * n + ((*str++ - '0') * sign);
	return (n);
}

int	exit_err(char *msg)
{
	printf("%s\n",msg);
	return (1);
}

void	exit_handler(int sig)
{
	(void)sig;
	write(1,"\n== bye bye! ==\n",17);
	exit(0);
}

int	send_str(char *str)
{
	int	i;
	int	len;
	int	bits;
	
	i = 0;
	len = (int)ft_strlen(str);
	bits = 8;
	while (i <= len)
	{
		bits = 8;
		while (--bits >= 0)
		{
			if  (*str & (1 << bits))
			{
				if (kill(pid,SIGUSR1) != 0)
					return (exit_err("SIGUSR1 kill err in handler\n"));
				write(1, "1", 1);
				usleep(100);
			}
				
			else
			{
				if (kill(pid,SIGUSR2) != 0)
					return (exit_err("SIGUSR2 kill err in handler\n"));
				write(1, "0", 1);
				usleep(100);
			}
		}
		str++;
		i++;
	}

	return (1);
}

void	handler_ack(int sig)
{
	if (sig == SIGUSR1) 
		write(1,"===== got ACK String sent successfully  ====== \n",49);
}

int	main(int argc, char *argv[])
{
	struct sigaction sa;

	if (!(argc == 3) || !_getint(argv[1]) || argv[1] == NULL)
		return (exit_err("Usage ./client pid message\n"));
		
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler_ack;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
			return (exit_err("sigaction client failed\n"));
	printf("client server pid=|%s| msg=|%s|\n", argv[1], argv[2]);
	pid = _getint(argv[1]);
	printf("server pid is integer %d \n",pid);

	if (signal(SIGINT, exit_handler) == SIG_ERR)
		return (exit_err("signal failed\n"));
		
	if (!send_str(argv[2]))
		return (exit_err("failed to send string\n"));





	/* wait for ack signal */
	while (1)
		pause();
	return (0);
}

/*
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);	
	usleep(50);
	s = kill(pid,SIGUSR1);
	printf("s %d\n", s);	
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);	
	usleep(50);
	s = kill(pid,SIGUSR1);
	printf("s %d\n", s);	
	usleep(50);

	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);	
	usleep(50);
	s = kill(pid,SIGUSR1);
	printf("s %d\n", s);	
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);
	usleep(50);
	s = kill(pid,SIGUSR2);
	printf("s %d\n", s);	
	usleep(50);
	s = kill(pid,SIGUSR1);
	printf("s %d\n", s);	
	usleep(50);
	*/