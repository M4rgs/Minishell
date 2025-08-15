/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:17:36 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_exit_builtin(char **args, t_fds fds)
{
	if (ft_strcmp(args[0], "exit") != 0)
		return (0);
	if (!fds.is_pipe)
		check_redirectons(&args);
	ft_exit(args);
	if (!fds.is_pipe)
		restore_std_fds(fds.out, fds.in);
	return (1);
}

int	handle_cd_builtin(char **args, char ***env, t_fds fds)
{
	if (!(ft_strcmp(args[0], "cd") == 0 && !fds.is_pipe))
		return (0);
	check_redirectons(&args);
	builti_cd(*env, args);
	restore_std_fds(fds.out, fds.in);
	return (1);
}

int	handle_export_builtin(char **args, char ***env, t_fds fds)
{
	if (ft_strcmp(args[0], "export") != 0)
		return (0);
	if (!fds.is_pipe)
		check_redirectons(&args);
	if (args[1] == NULL)
		builting_export_only(*env);
	else
		builtin_export(env, args);
	if (!fds.is_pipe)
		restore_std_fds(fds.out, fds.in);
	return (1);
}

int	handle_unset_builtin(char **args, char ***env, t_fds fds)
{
	if (ft_strcmp(args[0], "unset") != 0)
		return (0);
	if (!fds.is_pipe)
		check_redirectons(&args);
	builtin_unset(env, args);
	if (!fds.is_pipe)
		restore_std_fds(fds.out, fds.in);
	return (1);
}

int	check_builtin_pwd(char **args, char ***env, t_fds fds)
{
	if (ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "PWD") == 0)
	{
		if (!fds.is_pipe)
			check_redirectons(&args);
		builtin_pwd(*env);
		if (!fds.is_pipe)
			restore_std_fds(fds.out, fds.in);
		return (1);
	}
	return (0);
}
