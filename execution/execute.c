/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:05:43 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/20 17:08:25 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **copy_env(char **env)
{
    int i;
	int	j;

	i = 0;
	j = 0;
    while (env[i]) 
		i++;
    char **copy = ft_malloc(sizeof(char *) * (i + 1), 1);
    if (!copy)
		return NULL;
	while (j < i)
	{
		copy[j] = ft_strdup(env[j]);
		j++;
	}
	copy[j] = NULL;
    return copy;
}

void	join_declare(char **env)
{
	int	i;

	i = 0;
	char *tmp;
	while (env[i])
	{
		tmp = env[i];
		env [i] = ft_strjoin("declare -x ", tmp);
		i++;
	}
}

void	bubble_sort_env(char **env)
{
    int i;
	int	j;
    char *temp;
    int len;

	len = 0;
	j = 0;
    while (env[len])
		len++;
	while (i < len)
	{
		j = 0;
		while (j < (len -1))
		{
			if (env[j][0] > env[j + 1][0])
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	builting_export_only(char **env)
{
	int	i;

	i = 0;
	char	**temp_env;
	
	temp_env = copy_env(env);
	bubble_sort_env(temp_env);
	join_declare(temp_env);
	while (temp_env[i])
	{
		printf("%s\n", temp_env[i]);
		i++;
	}
}

int	check_builtings(t_tokenizer *tokenizer, t_infos *infos)
{
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
		return(1);
	}
	return (0);
}

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
	if (check_builtings(tokenizer, infos) == 1)
		return ;
	path = get_command_path(tokenizer->commands[0], infos->envp_info->env);
	if (!path)
	{
		printf("minishell: %s: command not found\n", tokenizer->commands[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		execve(path, tokenizer->commands, infos->envp_info->env);
		perror(tokenizer->commands[0]);
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
}
