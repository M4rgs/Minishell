/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:44:38 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/24 09:11:02 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*to_change(char *str, char c, char b)
{
	int		i;
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

int	ft_isdigit_string(char *c)
{
	int		i;

	i = 0;
	while (c[i])
	{
		if (c[i] <= '0' && c[i] >= '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char *input)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(input, ' ');
	if (ft_strcmp(splitted[0], "exit") == 0)
	{
		if (splitted[1] && ft_isdigit_string(splitted[1]) == 0)
			g_last_exit_status = ft_atoi(splitted[1]);
		printf("exit\n");
		ft_malloc(0, 0);
		exit(g_last_exit_status);
	}
	else
		return ;
}
