/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:05:43 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/17 03:41:12 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_direct_path(t_tokenizer *tokenizer, \
	t_infos *infos, char **path)
{
	int	ret;

	ret = check_command_path(tokenizer->commands[0], path);
	if (ret != -1 && ret != 0)
	{
		exit_status_value(ret, 1);
		return (1);
	}
	if (ret == -1)
	{
		*path = get_command_path(tokenizer->commands[0], infos->envp_info->env);
		if (!(*path))
		{
			exit_status_value(127, 1);
			print_error(tokenizer->commands[0], ": command not found\n");
			return (1);
		}
	}
	return (0);
}

static void	start_child(t_tokenizer *tokenizer, t_infos *infos, char *path)
{
	check_redirectons(&tokenizer->commands);
	execve(path, tokenizer->commands, infos->envp_info->env);
	ft_putstr_fd(CMD_NOT_FND, 2);
	exit(127);
}

static int	start_execute(t_tokenizer *tokenizer, t_infos *infos)
{
	pid_t	pid;
	char	*path;
	int		status;

	if (check_builtings(tokenizer->commands, &infos->envp_info->env, 0) == 1)
		return (1);
	if (tokenizer->is_heredoc)
		return (ft_heredoc_init(tokenizer->commands,
				infos->envp_info->env, tokenizer), 1);
	if (check_direct_path(tokenizer, infos, &path))
		return (1);
	g_signal_flag = 2;
	signal(SIGQUIT, signal_handling);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
		start_child(tokenizer, infos, path);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status_value(WEXITSTATUS(status), 1);
	return (signal(SIGQUIT, SIG_IGN), g_signal_flag = 0, 0);
}

void	execute_commands(t_tokenizer *tokenizer, t_infos *infos)
{
	if (!tokenizer->commands || !tokenizer->commands[0])
		return ;
	if (tokenizer->itispipe == 1)
		return (it_is_pipe(infos->envp_info->env, tokenizer));
	start_execute(tokenizer, infos);
}
