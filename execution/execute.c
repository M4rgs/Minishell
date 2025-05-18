/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:05:43 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/18 13:00:51 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_index(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

int	add_env_var(char ***env, const char *entry)
{
	char	**new_env;
	char	*key;
	char	*new_value;
	char	*old_value;
	int		i;
	int		index;
	int		append;

	append = 0;
	if (ft_strnstr(entry, "+=", ft_strlen(entry)))
	{
		append = 1;
		key = ft_substr(entry, 0, ft_strchr(entry, '+') - entry);
	}
	else if (ft_strchr(entry, '='))
		key = ft_substr(entry, 0, ft_strchr(entry, '=') - entry);
	else
		key = ft_strdup(entry);
	if (!key)
		return (0);

	index = get_env_index(*env, key);

	// ✅ Case: Append when key exists
	if (append && index != -1)
	{
		old_value = ft_strchr((*env)[index], '=') + 1;
		new_value = ft_strjoin(old_value, ft_strchr(entry, '=') + 1);
		free((*env)[index]);
		(*env)[index] = ft_strjoin3(key, "=", new_value);
		free(new_value);
		free(key);
		return (1);
	}

	// ✅ Case: Append when key DOESN’T exist — treat as normal assign
	if (append && index == -1)
	{
		char *assign = ft_strjoin3(key, "=", ft_strchr(entry, '=') + 1);
		free(key);
		return add_env_var(env, assign); // Recursive call with real assignment
	}

	// ✅ Key exists: replace or declare
	if (index != -1)
	{
		free((*env)[index]);
		if (ft_strchr(entry, '='))
			(*env)[index] = ft_strdup(entry);
		else
			(*env)[index] = ft_strjoin(key, "=");
		free(key);
		return (1);
	}

	// ✅ Add new env entry
	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (0);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	if (ft_strchr(entry, '='))
		new_env[i] = ft_strdup(entry);
	else
	{
		free(key);
		return (1);
	}
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	free(key);
	return (1);
}



int	remove_env_var(char ***env, const char *key)
{
	char	**new_env;
	int		index;
	int		i;
	int		j;

	index = get_env_index(*env, key);
	if (index == -1)
		return (0);
	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (0);
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (i != index)
			new_env[j++] = (*env)[i];
		else
			free((*env)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (1);
}

int	builtin_export(t_infos *infos, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		add_env_var(&infos->envp_info->env, args[i]);
		i++;
	}
	return (0);
}

int	builtin_unset(t_infos *infos, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(&infos->envp_info->env, args[i]);
		i++;
	}
	return (0);
}

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*partial;
	char	*full_path;
	int		i;

	i = 0;
	path_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		partial = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(partial, cmd);
		free(partial);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
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
	free(path);
}

