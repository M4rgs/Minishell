/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:37:48 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/19 01:44:02 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipes_in_child(t_pipe_tokenizer *pt, \
	char ***pipe_commands, char **env)
{
	setup_pipe_fds(pt);
	exec_pipe_command(pt, pipe_commands, env);
	return (0);
}

int	create_pipes_and_fork(t_pipe_tokenizer *pt, \
	char ***pipe_commands, char **env)
{
	pid_t	pid;
	int		j;

	pt->pipefds = ft_malloc(sizeof(int) * 2 * (pt->cmd_count - 1), 1);
	pt->i = -1;
	while (++pt->i < pt->cmd_count - 1)
	{
		if (pipe(pt->pipefds + pt->i * 2) == -1)
			return (perror("pipe"), -1);
	}
	pt->i = -1;
	g_signal_flag = 2;
	while (++pt->i < pt->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), -1);
		if (pid == 0)
			pipes_in_child(pt, pipe_commands, env);
	}
	j = 0;
	while (j < 2 * (pt->cmd_count - 1))
		close(pt->pipefds[j++]);
	return (g_signal_flag = 0, 0);
}

void	execute_piped_commands(t_pipe_tokenizer *pt, \
	char ***pipe_commands, int cmd_count, char **env)
{
	int					i;
	int					status;

	pt->cmd_count = cmd_count;
	if (create_pipes_and_fork(pt, pipe_commands, env) == -1)
		return ;
	i = 0;
	while (i < cmd_count)
	{
		wait(&status);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				exit_status_value(WEXITSTATUS(status), 1);
			else
				exit_status_value(0, 1);
		}
		i++;
	}
}

char	***spliting_by_pipes(t_pipe_tokenizer *pt, t_tokenizer *tokenizer)
{
	pt->cmds_allocated = count_pipes(tokenizer->commands);
	pt->pipe_commands = \
		ft_malloc(sizeof(char **) * (pt->cmds_allocated + 1), 1);
	pt->i = 0;
	pt->cmd_i = 0;
	pt->start = 0;
	while (tokenizer->commands[pt->i])
	{
		if (ft_strcmp(tokenizer->commands[pt->i], "|") == 0
			|| tokenizer->commands[pt->i + 1] == NULL)
		{
			if (ft_strcmp(tokenizer->commands[pt->i], "|") == 0)
				pt->end = pt->i;
			else
				pt->end = pt->i + 1;
			pt->pipe_commands[pt->cmd_i] = \
				copy_command_range(tokenizer->commands, pt->start, pt->end);
			pt->cmd_i++;
			pt->start = pt->i + 1;
		}
		pt->i++;
	}
	pt->pipe_commands[pt->cmd_i] = NULL;
	pt->cmd_count = pt->cmd_i;
	return (pt->pipe_commands);
}

void	it_is_pipe(char **env, t_tokenizer *tokenizer)
{
	t_pipe_tokenizer	*pt;

	pt = ft_malloc(sizeof(t_pipe_tokenizer), 1);
	pt->tokenizer = tokenizer;
	tokenizer->itispipe = 0;
	spliting_by_pipes(pt, tokenizer);
	process_all_heredocs(pt->pipe_commands, env, tokenizer);
	execute_piped_commands(pt, pt->pipe_commands, pt->cmd_count, env);
}
