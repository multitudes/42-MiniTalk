/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:55 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 20:25:32 by lbrusa           ###   ########.fr       */
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

void	_print_pid(void)
{
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	write(1, "server pid ", 12);
	write(1, pid_str, ft_strlen(pid_str));
	write(1, NEWLINE, 1);
}

void	exit_handler(int sig)
{
	(void)sig;
	write(1, "\n== bye bye! ==\n", 17);
	exit(0);
}

int	_exit_err(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return (1);
}
