/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:04:25 by tamounir          #+#    #+#             */
/*   Updated: 2024/11/04 10:39:21 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc(ft_strlen(s1) + 1);
	if (dest == NULL)
	{
		return (NULL);
	}
	else
	{
		while (s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}
