/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:54:58 by tamounir          #+#    #+#             */
/*   Updated: 2024/11/02 21:08:52 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;
	size_t	ff;

	srclen = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (srclen);
	destlen = ft_strlen(dst);
	ff = destlen;
	if (dstsize <= destlen)
		return (srclen + dstsize);
	i = 0;
	while (i + 1 + destlen < dstsize && src[i])
	{
		dst[ff] = src[i];
		i++;
		ff++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}
