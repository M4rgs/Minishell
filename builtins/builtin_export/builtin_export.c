/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:30:14 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/16 05:14:18 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_env_entry(char ***env, char *key, char *value, int append)
{
	char	*new_entry;
	int		index;

	new_entry = create_env_entry(*env, key, value, append);
	if (!new_entry)
		return (0);
	index = find_env_index(*env, key);
	if (index != -1)
	{
		(*env)[index] = new_entry;
		return (1);
	}
	return (insert_new_env(env, new_entry));
}

int	parse_export_arg(char *arg, char **key, char **value, int *append)
{
	char	*equal;

	*append = 0;
	equal = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (equal)
	{
		*append = 1;
		*key = ft_substr(arg, 0, equal - arg);
		*value = ft_strdup(equal + 2);
	}
	else
	{
		equal = ft_strchr(arg, '=');
		if (equal)
		{
			*key = ft_substr(arg, 0, equal - arg);
			*value = ft_strdup(equal + 1);
		}
		else
		{
			*key = ft_strdup(arg);
			*value = ft_strdup("");
		}
	}
	return (*key && *value);
}

static int	parse_and_add_export(char ***env, char *arg)
{
	char	*key;
	char	*value;
	int		append;

	if (!is_valid_identifier(arg, 1))
	{
		exit_status_value(1, 1);
		ft_putstr_fd("Minishell: export: `': not a valid identifier\n", 2);
		return (0);
	}
	if (!parse_export_arg(arg, &key, &value, &append))
		return (0);
	return (update_env_entry(env, key, value, append));
}

int	builtin_export(char ***env, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!parse_and_add_export(env, args[i]))
			return (0);
		i++;
	}
	return (1);
}
