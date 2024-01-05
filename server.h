/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:10 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/05 15:27:15 by lbrusa           ###   ########.fr       */
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

// typedef void (*sighandler_t)(int, siginfo_t, void*);
typedef void (*sighandler_t)(int);

void	sighandler(int sig, siginfo_t *siginfo, void *ucontext);


#endif