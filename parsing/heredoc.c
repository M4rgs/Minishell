/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:39 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/20 03:06:28 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute__heredoc(char **new_cmds, char *path, char **envp, char *file)
{
	pid_t	pid;
	int		fd;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		fd = open(file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		execve(path, new_cmds, envp);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
	}
	return (0);
}

char **extract_heredoc_infs(char **cmds, char **out_delimiter)
{
	int		i = 0;
	int		j = 0;
	int		heredoc_index;
	char	**new_cmds;
	int 	count;

	count = 0;
	heredoc_index = -1;
	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], "<<") == 0)
		{
			heredoc_index = i;
			break;
		}
		i++;
	}
	if (heredoc_index == -1 || cmds[heredoc_index + 1] == NULL)
		return (NULL);
	*out_delimiter = cmds[heredoc_index + 1];
	i = 0;
	while (cmds[i])
	{
		if (i != heredoc_index && i != heredoc_index + 1)
			count++;
		i++;
	}
	new_cmds = ft_malloc(sizeof(char *) * (count + 1), 1);
	i = 0;
	while (cmds[i])
	{
		if (i != heredoc_index && i != heredoc_index + 1)
			new_cmds[j++] = cmds[i];
		i++;
	}
	new_cmds[j] = NULL;
	return (new_cmds);
}

int	heredoc_input(char *delimiter, char *file, t_infos *infos)
{
	char	*input;
	int		fd;
	pid_t	pid;

	unlink(file);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd);
		return (0);
	}

	if (pid == 0)
	{
		while (1)
		{
			input = readline(">> ");
			if (!input)
				break;
			if (infos->tokenizer->has_to_expand == 1)
				input = expand_vars_in_string(input, infos->envp_info->env);
			if (ft_strcmp(input, delimiter) == 0)
			{
				free(input);
				break;
			}
			ft_putstr_fd(input, fd);
			ft_putstr_fd("\n", fd);
			free(input);
		}
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd);
	}
	return (1);
}

int	ft_heredoc_init(char **cmds, t_infos *infos)
{
	char	*delimiter;
	char	**new_cmds;
	char	*path;
	char	*file;
	char 	*ito_file;

	ito_file = ft_itoa(rand());
	file = ft_strjoin("/tmp/", ito_file);
	new_cmds = extract_heredoc_infs(cmds, &delimiter);
	if (!new_cmds)
		return (0);
	path = get_command_path(new_cmds[0], infos->envp_info->env);
	if (!heredoc_input(delimiter, file, infos))
		return (0);
	execute__heredoc(new_cmds, path, infos->envp_info->env, file);
	return (1);
}
