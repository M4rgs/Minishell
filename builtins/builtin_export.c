/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:30:14 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/20 15:12:20 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**expand_env_array(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	//ft_malloc((void ***)&new_env, NULL, 1, (sizeof(char *) * (i + 2)));
	new_env = ft_malloc((sizeof(char *) * (i + 2)), 1);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i + 1] = NULL;
	return (new_env);
}

int	create_env_var(char ***env, const char *entry, char *key)
{
	char	**new_env;
	int		i;

	new_env = expand_env_array(*env);
	if (!new_env)
	{
		//free(key);
		return (0);
	}
	i = 0;
	while ((*env)[i])
		i++;
	if (ft_strchr(entry, '='))
		new_env[i] = ft_strdup(entry);
	else
	{
		//free(new_env);
		//free(key);
		return (1);
	}
	//free(*env);
	*env = new_env;
	//free(key);
	return (1);
}

int	append_env_var(char ***env, char *key, const char *entry, int index)
{
	char	*old_value;
	char	*new_value;

	old_value = ft_strchr((*env)[index], '=') + 1;
	new_value = ft_strjoin(old_value, ft_strchr(entry, '=') + 1);
	//free((*env)[index]);
	(*env)[index] = ft_strjoin3(key, "=", new_value);
	//free(new_value);
	//free(key);
	return (1);
}

char	*extract_key(const char *entry, int *append)
{
	char	*key;

	*append = 0;
	if (ft_strnstr(entry, "+=", ft_strlen(entry)))
	{
		*append = 1;
		key = ft_substr(entry, 0, ft_strchr(entry, '+') - entry);
	}
	else if (ft_strchr(entry, '='))
		key = ft_substr(entry, 0, ft_strchr(entry, '=') - entry);
	else
		key = ft_strdup(entry);
	return (key);
}

int	add_env_var(char ***env, const char *entry)
{
	char	*key;
	int		index;
	int		append;
	char	*assign;

	key = extract_key(entry, &append);
	if (!key)
		return (0);
	index = get_env_index(*env, key);
	if (append && index != -1)
		return (append_env_var(env, key, entry, index));
	if (append && index == -1)
	{
		assign = ft_strjoin3(key, "=", ft_strchr(entry, '=') + 1);
		//free(key);
		return (add_env_var(env, assign));
	}
	if (index != -1)
	{
		//free((*env)[index]);
		(*env)[index] = ft_strchr(entry, '=') ? ft_strdup(entry) : ft_strjoin(key, "=");
		//free(key);
		return (1);
	}
	return (create_env_var(env, entry, key));
}

int	builtin_export(t_infos *infos, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		add_env_var(&infos->envp_info->env, args[i]);
		i++;
	}
	return (0);
}
