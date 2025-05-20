/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:05:43 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/20 15:05:49 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
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
		//free(full_path);
		//full_path = NULL;
		i++;
	}
	ft_free_split(paths);
	return (full_path);
}

void	execute_commands(t_tokenizer *tokenizer, t_infos *infos)
{
	pid_t	pid;
	char	*path;

	if (!tokenizer->commands || !tokenizer->commands[0])
		return ;
	if (ft_strcmp(tokenizer->commands[0], "export") == 0)
	{
		builtin_export(infos, tokenizer->commands);
		return ;
	}
	else if (ft_strcmp(tokenizer->commands[0], "unset") == 0)
	{
		builtin_unset(infos, tokenizer->commands);
		return ;
	}
	path = get_command_path(tokenizer->commands[0], infos->envp_info->env);
	if (!path)
	{
		printf("minishell: %s: command not found\n", tokenizer->commands[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, tokenizer->commands, infos->envp_info->env);
		perror("execve failed");
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
}
