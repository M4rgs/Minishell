/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:12:13 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/18 23:17:30 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size, int flag)
{
	static void	*allocated[MAX_ALLOC];
	static int	counter = 0;
	void		*ptr;
	int			i;

	if (flag == 1)
	{
		if (counter >= MAX_ALLOC)
			return (NULL);
		ptr = malloc(size);
		if (!ptr)
			return (NULL);
		allocated[counter++] = ptr;
	}
	if (flag == 0)
	{
		i = 0;
		while (i < counter)
		{
			free(allocated[i]);
			allocated[i] = NULL;
			i++;
		}
		counter = 0;
	}
	return (ptr);
}
