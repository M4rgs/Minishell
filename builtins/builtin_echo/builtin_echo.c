/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 04:33:35 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_n_flags(int argc, char **cmds, int *new_line)
{
	int	i;
	int	j;

	i = 1;
	*new_line = 1;
	while (i < argc && ft_strncmp(cmds[i], "-n", 2) == 0)
	{
		j = 2;
		while (cmds[i][j] && cmds[i][j] == 'n')
			j++;
		if (cmds[i][j])
			break ;
		*new_line = 0;
		i++;
	}
	return (i);
}

int	builtin_echo(int argc, char **cmds)
{
	int	i;
	int	new_line;

	i = skip_n_flags(argc, cmds, &new_line);
	while (i < argc)
	{
		printf("%s", cmds[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
