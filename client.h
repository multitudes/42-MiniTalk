/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:21 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 21:27:41 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "libft/libft.h"

void	exit_handler(int sig);
void	handler_ack(int sig);
int		_exit_err(char *msg);
int		_getint(const char *str);
int		_send_str(char *str);

#endif