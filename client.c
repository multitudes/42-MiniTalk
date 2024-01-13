/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:36 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/13 13:55:19 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/* 
I need a static variable because there is no way of passing this info 
which I get from the command line args, to the handler of a signal. 
It has to be global.
*/
static pid_t	g_pid;

static void	ack_handler(int sig)
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
	sa.sa_handler = ack_handler;
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
