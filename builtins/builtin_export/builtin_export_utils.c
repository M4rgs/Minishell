/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 05:05:23 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	insert_new_env(char ***env, char *new_entry)
{
	char	**new_env;
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = ft_malloc(sizeof(char *) * (i + 2), 1);
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	*env = new_env;
	return (1);
}

int	find_env_index(char **env, char *key)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	is_valid_identifier_characters(const char *arg, int flag)
{
	int	i;

	if (!arg || arg[0] == '\0' || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			if (flag == 0)
				return (0);
			break ;
		}
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (i);
}

int	is_valid_identifier(const char *arg, int flag)
{
	int	i;

	i = is_valid_identifier_characters(arg, flag);
	if (i == 0)
		return (0);
	if (arg[i] == '+')
	{
		if (arg[i + 1] != '=')
			return (0);
		i += 2;
	}
	else if (arg[i] == '=')
		i++;
	return (1);
}

char	*create_env_entry(char **env, char *key, char *value, int append)
{
	int		index;
	char	*old_value;
	char	*joined;

	index = find_env_index(env, key);
	if (append && index != -1)
	{
		old_value = ft_strchr(env[index], '=') + 1;
		joined = ft_strjoin(old_value, value);
		return (ft_strjoin3(key, "=", joined));
	}
	return (ft_strjoin3(key, "=", value));
}
