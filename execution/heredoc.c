/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:39 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/26 14:27:52 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc_init(char **cmds, t_infos *infos, int i)
{
	char	*delimiter;
	pid_t	pid;
	char	*input;
	int fd;

	if (cmds[i + 1] == NULL)
		return (0);
	delimiter = cmds[i + 1];
	unlink("/tmp/heredoc.txt");
	fd = open("/tmp/heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			input = readline(">> ");
			if (!input)
				break;
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

int	run_heredoc_and_execute(char **cmds)
{
	int	heredoc_index = -1;
	for (int i = 0; cmds[i]; i++)
	{
		if (ft_strcmp(cmds[i], "<<") == 0)
		{
			heredoc_index = i;
			break;
		}
	}
	if (heredoc_index == -1 || cmds[heredoc_index + 1] == NULL)
		return (0);
	ft_heredoc_init(cmds, NULL, heredoc_index);
	cmds[heredoc_index] = NULL;
	pid_t pid = fork();
	if (pid == 0)
	{
		int fd = open("/tmp/heredoc.txt", O_RDONLY);
		if (fd < 0)
		{
			perror("open heredoc.txt");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		execvp(cmds[0], cmds);
		perror("execvp failed");
		exit(1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		unlink("/tmp/heredoc.txt");
	}
	return (1);
}
