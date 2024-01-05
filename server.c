/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:47:25 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 18:29:44 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	_decoder(char *byte)
{
	int	i;
	int	dec;

	i = 0;
	dec = 0;
	while (i < 8)
		dec = dec * 2 + byte[i++] - '0';
	return (dec);
}

void	sighandler(int sig, siginfo_t *siginfo, void *ucontext)
{
	char		byte[9];
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

int	main(void)
{
	struct sigaction	act;

	_print_pid();
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_sigaction = sighandler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return (exit_err("sigaction failed\n"));
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		return (exit_err("sigaction failed\n"));
	if (signal(SIGINT, exit_handler) == SIG_ERR)
		return (exit_err("SIG_ERR signal failed\n"));
	while (1)
		pause();
	return (0);
}
