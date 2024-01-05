/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:46 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 21:58:55 by lbrusa           ###   ########.fr       */
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
