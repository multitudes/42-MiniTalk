/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:10 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/13 16:45:31 by lbrusa           ###   ########.fr       */
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

void	_print_pid(void);
int		_exit_err(char *msg);
int		_decoder(char *byte);

// libft funcs
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);


#endif