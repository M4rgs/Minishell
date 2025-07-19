/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:44:28 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/19 02:12:51 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char **env, const char *key)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (ft_strdup(ft_strchr(env[i], '=') + 1));
		i++;
	}
	return (NULL);
}

char	**default_env(void)
{
	char	**p;

	p = ft_malloc((sizeof(char *) * 3), 1);
	if (!p)
		return (NULL);
	p[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin");
	p[1] = ft_strdup("PWD=/home/tamounir/Desktop/Minishell");
	p[2] = NULL;
	return (p);
}
