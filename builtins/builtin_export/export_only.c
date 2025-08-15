/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:29:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**copy_env(char **env)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	copy = ft_malloc(sizeof(char *) * (i + 1), 1);
	while (j < i)
	{
		copy[j] = ft_strdup(env[j]);
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

void	join_declare(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = env[i];
		env [i] = ft_strjoin("declare -x ", tmp);
		i++;
	}
}

void	bubble_sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;
	int		len;

	len = 0;
	j = 0;
	i = 0;
	while (env[len])
		len++;
	while (i < len)
	{
		j = 0;
		while (j < (len -1))
		{
			if (env[j][0] > env[j + 1][0])
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	builting_export_only(char **env)
{
	int		i;
	char	**temp_env;

	i = 0;
	temp_env = copy_env(env);
	bubble_sort_env(temp_env);
	join_declare(temp_env);
	while (temp_env[i])
	{
		printf("%s\n", temp_env[i]);
		i++;
	}
}
