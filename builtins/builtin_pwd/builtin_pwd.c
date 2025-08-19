/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 04:13:25 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/18 20:40:27 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_pwd(char **env)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir)
		printf("%s\n", dir);
	else
	{
		dir = get_env_value(env, "PWD");
		if (dir)
			printf("%s\n", dir);
		else
			ft_putstr_fd("can't find pwd\n", 2);
	}
	free(dir);
	return (0);
}
