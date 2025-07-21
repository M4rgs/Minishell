/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:44:38 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/20 18:05:02 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*to_change(char *str, char c, char b)
{
	int i;
	char	*dest;

	i = 0;
	dest = ft_malloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		if (str[i] == c)
			dest[i] = b;
		else
			dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
