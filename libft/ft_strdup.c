/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:04:25 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/20 15:13:32 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dest;

	i = 0;
	//t_malloc((void ***)&dest, NULL, 1, (ft_strlen(s1) + 1));
	dest = ft_malloc((ft_strlen(s1) + 1), 1);
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
