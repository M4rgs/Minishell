/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:48:42 by tamounir          #+#    #+#             */
/*   Updated: 2024/11/01 20:33:51 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = len - 1;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!s && !d)
		return (NULL);
	if (dst > src)
	{
		while (i + 1 > 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	else
	{
		ft_memcpy(d, s, len);
	}
	return (dst);
}
