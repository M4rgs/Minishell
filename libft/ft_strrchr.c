/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:09:07 by tamounir          #+#    #+#             */
/*   Updated: 2024/10/29 22:48:56 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mylen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = mylen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (NULL);
}
