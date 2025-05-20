/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:35:51 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/20 09:54:02 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_env_var(char ***env, const char *key)
{
	char	**new_env;
	int		index;
	int		i;
	int		j;

	index = get_env_index(*env, key);
	if (index == -1)
		return (0);
	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (0);
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (i != index)
			new_env[j++] = (*env)[i];
		else
			free((*env)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (1);
}

int	builtin_unset(t_infos *infos, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(&infos->envp_info->env, args[i]);
		i++;
	}
	return (0);
}
