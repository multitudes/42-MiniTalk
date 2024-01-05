/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:10 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 20:25:32 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "libft/libft.h"

void	sighandler(int sig, siginfo_t *siginfo, void *ucontext);
void	_print_pid(void);
void	exit_handler(int sig);
int		_exit_err(char *msg);
int		_decoder(char *byte);

#endif