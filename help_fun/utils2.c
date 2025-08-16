/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:44:28 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/16 05:28:41 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	char	*pwd;

	p = ft_malloc((sizeof(char *) * 5), 1);
	p[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin");
	p[1] = ft_strdup("OLDPWD=");
	pwd = getcwd(NULL, 0);
	if (pwd)
		p[2] = ft_strdup(ft_strjoin("PWD=", pwd));
	else
		p[2] = ft_strdup("PWD=");
	p[3] = ft_strdup("SHLVL=1");
	p[4] = NULL;
	free(pwd);
	return (p);
}

int	exit_status_value(int value, int flag)
{
	static int	exit_status_value = 0;

	if (flag == 1)
		exit_status_value = value;
	return (exit_status_value);
}

int	is_double_operator(char c1, char c2)
{
	return ((c1 == '<' && c2 == '<') \
			|| (c1 == '>' && c2 == '>'));
}

int	is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
