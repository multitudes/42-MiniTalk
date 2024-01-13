/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:46 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/13 13:45:32 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	_exit_err(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return (1);
}

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
