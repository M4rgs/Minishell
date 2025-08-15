/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:53:19 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		odd;
	size_t	rzlt;

	i = 0;
	odd = 1;
	rzlt = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13) || str[i] == '"')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			odd = odd * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rzlt = rzlt * 10 + (str[i] - 48);
		if (rzlt > 9223372036854775807 && odd == -1)
			return (-1);
		if (rzlt > 9223372036854775807 && odd == 1)
			return (-2);
		i++;
	}
	return (rzlt * odd);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	dr;

	dr = count * size;
	if (count && size != dr / count)
		return (NULL);
	p = ft_malloc(count * size, 1);
	ft_bzero(p, count * size);
	return (p);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z' ))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}
