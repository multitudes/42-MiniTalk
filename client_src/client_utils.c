/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:46 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/13 17:59:12 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/*
not a handler - exits if the usage is wrong or pid given is
incorrect or not reachable
*/
int	_exit_err(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return (1);
}

/*
from the command line I get the pid in string format
here I convert it to int - not ft_atoi because it has to 
be only positivea and without extra chars
*/
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

/*
This is the way I encode and send the messages to the server
For every bit which is 1 I send a SIGUSR1 and a SIGUSR0 if 0
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
