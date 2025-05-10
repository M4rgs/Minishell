/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:52:23 by tamounir          #+#    #+#             */
/*   Updated: 2024/10/27 20:48:43 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	dr;

	dr = count * size;
	if (count && size != dr / count)
		return (NULL);
	p = malloc (count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
