/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:35:51 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_env_without_key(char **env, int remove_index)
{
	int		i;
	int		j;
	char	**new_env;
	int		count;

	i = 0;
	while (env[i])
		i++;
	count = i;
	new_env = ft_malloc(sizeof(char *) * count, 1);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != remove_index)
			new_env[j++] = env[i];
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	remove_env_var(char ***env, char *key)
{
	int		index;
	char	**new_env;

	if (!is_valid_identifier(key, 0))
	{
		exit_status_value(1, 1);
		ft_putstr_fd("Minishell : unset: `': not a valid identifier\n", 2);
		return (0);
	}
	index = get_env_index(*env, key);
	if (index == -1)
		return (0);
	new_env = create_env_without_key(*env, index);
	if (!new_env)
		return (0);
	*env = new_env;
	return (1);
}

int	builtin_unset(char ***env, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(env, args[i]);
		i++;
	}
	return (0);
}
