/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:55 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/13 18:02:10 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
utility function to decode an array of 8 bits to a byte or a char
*/
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

/*
At the start the server will print its own pid
this function does just that
*/
void	_print_pid(void)
{
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	write(1, "server pid ", 12);
	write(1, pid_str, ft_strlen(pid_str));
	write(1, NEWLINE, 1);
	free(pid_str);
}

/*
Not a handler - it will exit if there is an error
*/
int	_exit_err(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return (1);
}
