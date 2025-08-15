/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 04:01:35 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_redirection(char *arg)
{
	return (ft_strcmp(arg, ">") == 0
		|| ft_strcmp(arg, "<") == 0
		|| ft_strcmp(arg, ">>") == 0
		|| ft_strcmp(arg, "<<") == 0);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**new_cmds_no_redi(char **args)
{
	int		i;
	int		k;
	int		len;
	char	**new_cmds;

	len = count_args(args);
	if (len < 3)
		return (args);
	new_cmds = ft_malloc(sizeof(char *) * (len + 1), 1);
	i = 0;
	k = 0;
	while (args[i])
	{
		if (is_redirection(args[i]))
		{
			if (!args[i + 1])
				break ;
			i += 2;
			continue ;
		}
		new_cmds[k++] = args[i++];
	}
	new_cmds[k] = NULL;
	return (new_cmds);
}
