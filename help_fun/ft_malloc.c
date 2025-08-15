/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:12:13 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char **allocated, int *count)
{
	int	i;

	i = 0;
	while (i < *count)
	{
		free(allocated[i]);
		allocated[i] = NULL;
		i++;
	}
	*count = 0;
}

void	*ft_malloc(size_t size, int flag)
{
	static void	*allocated[MAX_ALLOC];
	static int	counter = 0;
	void		*ptr;

	if (flag == 1)
	{
		if (counter >= MAX_ALLOC)
			return (NULL);
		ptr = malloc(size);
		if (!ptr)
		{
			ft_malloc(0, 0);
			ft_putstr_fd("error malloc\n", 1);
			exit(1);
		}
		allocated[counter++] = ptr;
		return (ptr);
	}
	if (flag == 0)
		ft_free((char **)allocated, &counter);
	return (NULL);
}
