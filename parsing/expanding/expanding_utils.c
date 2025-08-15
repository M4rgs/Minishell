/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:21:40 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_empty_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			args[j++] = args[i];
		i++;
	}
	args[j] = NULL;
}

void	trunc_expanded_spaces(char ***new_cmds, char *expanded, int *k)
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = ft_split(expanded, ' ');
	while (splitted[i])
	{
		(*new_cmds)[(*k)++] = ft_strdup(splitted[i]);
		i++;
	}
}

char	*handle_dollar(char *str, int *i, char **env, char *result)
{
	char	*tmp;

	(*i)++;
	if (str[*i] == '?')
		return (exit_status_expanding(result, i));
	else if (str[*i] >= '0' && str[*i] <= '9')
	{
		(*i)++;
		return (result);
	}
	else if (ft_isalnum(str[*i]) || str[*i] == '_')
		return (expand_env_var(str, i, env, result));
	else
	{
		tmp = ft_strjoin_char(result, '$');
		return (tmp);
	}
}

char	*exit_status_expanding(char *rzlt, int *i)
{
	char	*exit_string;
	char	*tmp;

	exit_string = ft_itoa(exit_status_value(-1, -1));
	tmp = ft_strjoin(rzlt, exit_string);
	(*i)++;
	return (tmp);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin(s, tmp));
}
