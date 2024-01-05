/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:36 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/04 22:46:05 by lbrusa           ###   ########.fr       */
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

void	handler(int sig)
{

	if (sig == SIGUSR1) 
		write(1,"got it ====== \n",16);
}

int	main(int argc, char *argv[])
{
	pid_t pid;
	int s;
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
			return (exit_err("sigaction client failed\n"));
	
	if (!(argc == 3) || !_getint(argv[1]) || argv[1] == NULL)
		return (exit_err("Usage ./client pid message\n"));
	printf("client server pid=|%s| msg=|%s|\n", argv[1], argv[2]);
	pid = _getint(argv[1]);
	printf("pid is integer %d \n",pid);

	

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
	while (1)
		pause();
	return (0);
}