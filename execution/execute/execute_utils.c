/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:43:59 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 03:20:04 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	save_std_fds(int *saved_stdout, int *saved_stdin)
{
	*saved_stdout = dup(STDOUT_FILENO);
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdout < 0 || *saved_stdin < 0)
		return (1);
	return (0);
}

void	restore_std_fds(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*partial;
	char	*full_path;
	int		i;

	path_env = find_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		partial = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(partial, cmd);
		if (access(full_path, X_OK) == 0)
			break ;
		full_path = NULL;
		i++;
	}
	return (full_path);
}

void	print_error(char *cmd, char *msg)
{
	write(2, "Minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
}

int	check_command_path(char *cmd, char **path)
{
	struct stat	sb;

	if (ft_strchr(cmd, '/') == NULL)
		return (-1);
	if (stat(cmd, &sb) == -1)
	{
		print_error(cmd, ": No such file or directory\n");
		return (127);
	}
	if (S_ISDIR(sb.st_mode))
	{
		print_error(cmd, ": is a directory\n");
		return (126);
	}
	if (access(cmd, X_OK) != 0)
	{
		print_error(cmd, ": Permission denied\n");
		return (126);
	}
	*path = ft_strdup(cmd);
	return (0);
}
