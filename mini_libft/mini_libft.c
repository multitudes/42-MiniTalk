/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:51:55 by lbrusa            #+#    #+#             */
/*   Updated: 2024/01/13 17:00:41 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_itoa(int n)
{
	int		i;
	int		minus;
	char	temp[12];

	i = 1;
	minus = 1;
	temp[11] = '\0';
	if (n >= 0)
	{
		n *= -1;
		minus = 0;
	}
	temp[11 - i++] = '0' - (n % 10);
	n /= 10;
	while (n != 0)
	{
		temp[11 - i++] = '0' - (n % 10);
		n /= 10;
	}
	if (minus)
		temp[11 - i++] = '-';
	return (ft_strdup(&temp[11 - i + 1]));
}
