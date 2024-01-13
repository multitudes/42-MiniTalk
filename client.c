/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:36 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/06 12:06:21 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#define DELAY 150

/* 
I need a static variable because there is no way of passing this info 
which I get from the command line args, to the handler of a signal. 
It has to be global.
*/
static pid_t	g_pid;

static void	handler_ack(int sig)
{
	(void)sig;
	write(1, "\n===== Server ACK msg received successfully  ====== \n", 54);
	exit(0);
}

static void	exit_handler(int sig)
{
	(void)sig;
	write(1, "\n== bye bye! ==\n", 17);
	exit(0);
}

/*
FOR DEBUG
	write(1,"1",1);
	write(1,"0",1);
*/
int	_send_str(char *str)
{
	int	len;
	int	bits;

	len = (int)ft_strlen(str);
	while (len-- >= 0)
	{
		bits = 8;
		while (--bits >= 0)
		{
			if (*str & (1 << bits))
			{
				if (kill(g_pid, SIGUSR1) != 0)
					return (_exit_err("pid error\n"));
				usleep(DELAY);
			}
			else
			{
				if (kill(g_pid, SIGUSR2) != 0)
					return (_exit_err("pid error\n"));
				usleep(DELAY);
			}
		}
		str++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	g_pid = _getint(argv[1]);
	if (!(g_pid) || kill(g_pid, 0) != 0)
		return (_exit_err("pid error\n"));
	if (!(argc == 3) || !argv[1])
		return (_exit_err("Usage ./client pid message\n"));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler_ack;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (_exit_err("sigaction client failed\n"));
	if (signal(SIGINT, exit_handler) == SIG_ERR)
		return (_exit_err("signal failed\n"));
	if (!_send_str(argv[2]))
		return (_exit_err("\nFailed to send string\n"));
	while (1)
		pause();
	return (0);
}
