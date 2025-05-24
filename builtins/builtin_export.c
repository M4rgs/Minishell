/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:30:14 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/24 00:47:25 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	update_env_entry(char ***env, char *key, char *value, int append)
{
	int		index;
	char	*old;
	char	*new_entry;
	char	*joined;
	int		i;
	char	**new_env;

	index = find_env_index(*env, key);
	if (append && index != -1)
	{
		old = ft_strchr((*env)[index], '=') + 1;
		joined = ft_strjoin(old, value);
		new_entry = ft_strjoin3(key, "=", joined);
	}
	else
		new_entry = ft_strjoin3(key, "=", value);
	if (index != -1)
	{
		(*env)[index] = new_entry;
		return (1);
	}
	i = 0;
	while ((*env)[i])
		i++;
	new_env = ft_malloc(sizeof(char *) * (i + 2), 1);
	if (!new_env)
		return (0);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	*env = new_env;
	return (1);
}

int	parse_and_add_export(char ***env, char *arg)
{
	char	*key;
	char	*value;
	char	*plus_eq;
	char	*equal;
	int		append;

	append = 0;
	key = NULL;
	value = NULL;
	plus_eq = ft_strnstr(arg, "+=", ft_strlen(arg));
	equal = ft_strchr(arg, '=');
	if (plus_eq)
	{
		append = 1;
		key = ft_substr(arg, 0, plus_eq - arg);
		value = ft_strdup(plus_eq + 2);
	}
	else if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = ft_strdup("");
	}
	if (!key || !value)
		return (0);
	return (update_env_entry(env, key, value, append));
}

int	builtin_export(t_infos *infos, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!parse_and_add_export(&infos->envp_info->env, args[i]))
			return (0);
		i++;
	}
	return (1);
}
