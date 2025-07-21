/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:05:43 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/21 12:55:57 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtings(t_tokenizer *tokenizer, t_infos *infos)
{
	int	i;

	i = 0;
	while (tokenizer->commands[i])
	{
		if (tokenizer->is_heredoc == 1)
			return (ft_heredoc_init(tokenizer->commands, infos, tokenizer));
		i++;
	}
	if (ft_strcmp(tokenizer->commands[0], "export") == 0)
	{
		if (tokenizer->commands[1] == NULL)
		{
			builting_export_only(infos->envp_info->env);
			return (1);
		}
		builtin_export(infos, tokenizer->commands);
		return (1);
	}
	else if (ft_strcmp(tokenizer->commands[0], "unset") == 0)
	{
		builtin_unset(infos, tokenizer->commands);
		return (1);
	}
	return (0);
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

void	execute_commands(t_tokenizer *tokenizer, t_infos *infos)
{
	pid_t	pid;
	char	*path;
	int		status;

	if (!tokenizer->commands || !tokenizer->commands[0])
		return ;
	if (check_builtings(tokenizer, infos) == 1)
		return ;
	path = get_command_path(tokenizer->commands[0], infos->envp_info->env);
	if (!path)
	{
		printf("minishell: %s: command not found\n", tokenizer->commands[0]);
		g_last_exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		execve(path, tokenizer->commands, infos->envp_info->env);
		perror("Minishell");
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
	}
}
