/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:06:42 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_builtin_echo(char **args, t_fds fds)
{
	int	j;

	if (ft_strcmp(args[0], "echo") == 0)
	{
		if (!fds.is_pipe)
			check_redirectons(&args);
		j = 0;
		while (args[j])
			j++;
		builtin_echo(j, args);
		if (!fds.is_pipe)
			restore_std_fds(fds.out, fds.in);
		return (1);
	}
	return (0);
}

int	check_builtings(char **args, char ***env, \
	int is_pipe)
{
	t_fds	fds;

	if (!args || !args[0])
		return (0);
	fds.is_pipe = is_pipe;
	fds.out = -1;
	fds.in = -1;
	if (!fds.is_pipe && save_std_fds(&fds.out, &fds.in))
		return (1);
	if (handle_exit_builtin(args, fds)
		|| handle_cd_builtin(args, env, fds)
		|| handle_export_builtin(args, env, fds)
		|| handle_unset_builtin(args, env, fds)
		|| check_builtin_pwd(args, env, fds)
		|| check_builtin_echo(args, fds))
		return (1);
	if (!fds.is_pipe)
		restore_std_fds(fds.out, fds.in);
	return (0);
}
