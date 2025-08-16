/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 04:01:40 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/16 01:33:15 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_heredoc_child(char **new_cmds, \
	char *path, char **envp, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
	check_redirectons(&new_cmds);
	execve(path, new_cmds, envp);
	ft_putstr_fd("minishell: command not found\n", 2);
	exit(127);
}

int	execute__heredoc(char **new_cmds, char *path, char **envp, char *file)
{
	pid_t	pid;
	int		status;
	int		saved_stdout;
	int		saved_stdin;

	if (save_std_fds(&saved_stdout, &saved_stdin) || \
		check_builtings(new_cmds, &envp, 0))
		return (1);
	pid = fork();
	if (pid == -1)
		return (close(saved_stdin), close(saved_stdout), 1);
	if (pid == 0)
		execute_heredoc_child(new_cmds, path, envp, file);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_status_value(WEXITSTATUS(status), 1);
		else
			exit_status_value(1, 1);
		restore_std_fds(saved_stdout, saved_stdin);
	}
	else
		return (restore_std_fds(saved_stdout, saved_stdin), perror("fork"), 1);
	return (0);
}

char	**extract_heredoc_infs(char **cmds, int *heredoc_index)
{
	int		count;
	char	**new_cmds;

	*heredoc_index = find_heredoc_index(cmds);
	if (*heredoc_index == -1 || cmds[*heredoc_index + 1] == NULL)
		return (handle_heredoc_syntax_error());
	count = count_cmds(cmds, *heredoc_index);
	new_cmds = ft_malloc(sizeof(char *) * (count + 1), 1);
	copy_cmds(cmds, new_cmds, *heredoc_index);
	return (new_cmds);
}

int	heredoc_input(char *delimiter, char *file, \
	char **env, t_tokenizer *tokenizer)
{
	int		fd;
	pid_t	pid;
	int		status;

	unlink(file);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		return (perror("open"), 0);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(fd), 0);
	if (pid == 0)
		heredoc_child(fd, delimiter, env, tokenizer);
	else
	{
		close(fd);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status))
			return (unlink(file), 0);
	}
	return (1);
}

int	ft_heredoc_init(char **cmds, char **env, t_tokenizer *tokenizer)
{
	char	*delimiter;
	char	**new_cmds;
	char	*path;
	char	*file;
	int		heredoc_index;

	tokenizer->is_heredoc = 0;
	g_signal_flag = 1;
	file = ft_strjoin("/tmp/here_file_", ft_itoa(getpid()));
	new_cmds = extract_heredoc_infs(cmds, &heredoc_index);
	delimiter = expand_vars_in_string(cmds[heredoc_index + 1], env, tokenizer);
	if (!new_cmds)
		return (1);
	path = get_command_path(new_cmds[0], env);
	if (!heredoc_input(delimiter, file, env, tokenizer))
		return (1);
	execute__heredoc(new_cmds, path, env, file);
	g_signal_flag = 0;
	unlink(file);
	return (1);
}
