/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 22:06:50 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builti_cd(char **env, char **args)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_value(env, "HOME");
		if (!path || chdir(path) != 0)
			ft_putstr_fd(CD_ERR, 1);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("Minishell: ");
			exit_status_value(1, 1);
		}
	}
}
