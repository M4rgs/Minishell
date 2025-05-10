/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:22:34 by tamounir          #+#    #+#             */
/*   Updated: 2024/10/31 00:54:45 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst != src)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
