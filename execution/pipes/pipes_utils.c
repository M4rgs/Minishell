/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 04:03:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(char **tokens)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

char	**copy_command_range(char **commands, int start, int end)
{
	char	**cmd;
	int		size;
	int		j;

	size = end - start;
	cmd = ft_malloc(sizeof(char *) * (size + 1), 1);
	j = 0;
	while (j < size)
	{
		cmd[j] = ft_strdup(commands[start + j]);
		j++;
	}
	cmd[size] = NULL;
	return (cmd);
}

void	setup_pipe_fds(t_pipe_tokenizer *pt)
{
	int	j;

	if (pt->i != 0)
	{
		if (dup2(pt->pipefds[(pt->i - 1) * 2], STDIN_FILENO) == -1)
			exit(1);
	}
	if (pt->i != pt->cmd_count - 1)
	{
		if (dup2(pt->pipefds[pt->i * 2 + 1], STDOUT_FILENO) == -1)
			exit(1);
	}
	j = 0;
	while (j < 2 * (pt->cmd_count - 1))
	{
		close(pt->pipefds[j]);
		j++;
	}
}

void	exec_pipe_command(t_pipe_tokenizer *pt, \
	char ***pipe_commands, char **env)
{
	char	*path;
	int		ret;

	check_redirectons(&pipe_commands[pt->i]);
	if (check_builtings(pipe_commands[pt->i], &env, 1) == 1)
		exit(0);
	ret = check_command_path(pipe_commands[pt->i][0], &path);
	if (ret != -1 && ret != 0)
		exit(ret);
	else if (ret == -1)
	{
		path = get_command_path(pipe_commands[pt->i][0], env);
		if (!path)
		{
			print_error(pipe_commands[pt->i][0], ": command not found\n");
			exit(127);
		}
	}
	execve(path, pipe_commands[pt->i], env);
	ft_putstr_fd("Minishell : command not found\n", 2);
	exit(127);
}

void	process_all_heredocs(char ***pipe_commands, \
	char **env, t_tokenizer *tokenizer)
{
	int	i;
	int	j;

	i = 0;
	while (pipe_commands[i])
	{
		j = 0;
		while (pipe_commands[i][j])
		{
			if (ft_strcmp(pipe_commands[i][j], "<<") == 0)
				ft_heredoc_init(pipe_commands[i], env, tokenizer);
			j++;
		}
		i++;
	}
}
