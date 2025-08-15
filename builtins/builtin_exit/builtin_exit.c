/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:00:56 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*remove_quotes(const char *s)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = ft_malloc(len + 1, 1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (s[i] != '\'' && s[i] != '"' && s[i] != ' ')
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

static void	handle_exit_arguments(char **splitted)
{
	char	*exit_status;
	long	status;

	if (splitted[1])
		exit_status = remove_quotes(splitted[1]);
	else
		exit_status = NULL;
	if (splitted[1] && (ft_isdigit_string(exit_status) \
		|| ft_atol(exit_status, &status)))
		non_numeric_exit(splitted);
	if (splitted[1] && splitted[2])
	{
		exit_status_value(1, 1);
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd(EXIT_ERR_NU, 2);
		return ;
	}
	if (splitted[1])
		exit_status_value(status, 1);
	ft_putstr_fd("exit\n", 2);
	ft_malloc(0, 0);
	exit(exit_status_value(-1, -1));
}

void	ft_exit(char **args)
{
	if (!args || !args[0])
	{
		ft_malloc(0, 0);
		exit(exit_status_value(-1, -1));
	}
	handle_exit_arguments(args);
}
