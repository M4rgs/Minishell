/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:18 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/14 20:46:52 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_command_path(char *cmd, char **envp)
{
	char *path_env = NULL;
	char **paths;
	char *full_path;
	int i;

	for (i = 0; envp[i]; i++)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void execute_commands(t_tokenizer *tokenizer, t_infos *infos)
{
	pid_t pid;
	char *path;

	if (!tokenizer->commands || !tokenizer->commands[0])
		return;
	path = get_command_path(tokenizer->commands[0], infos->envp_info->env);
	if (!path)
	{
		printf("minishell: %s: command not found\n", tokenizer->commands[0]);
		return;
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

void	it_is_pipe(char *line, t_tokenizer *tokenizer)
{
	int		i;
	int		j;
	char	**lexxs;

	i = 0;
	j = 0;
	lexxs = ft_split(line, ' ');
	while (lexxs[i])
	{
		if (strcmp(lexxs[i], "|") == 0)
		{
			if ((i - 1 >= 0) && lexxs[i + 1] != NULL)
			{
				tokenizer->commands[j] = lexxs[i - 1];
				tokenizer->commands[j + 1] = lexxs[i + 1];
				j++;
			}
			else
				printf("Minishell: syntax error near unexpected token `|'\n");
		}
		i++;
	}
	
}

int	is_it_token(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (strcmp(s[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	handle_quotes(char *line, t_tokenizer *tokenizer)
{
	int		i = 0;
	int start;
	int cmd_i = 0;

	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\'')
		{
			start = ++i; 
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
				return (0);
			tokenizer->commands[cmd_i++] = strndup(&line[start], i - start);
			i++;
		}
		else if (line[i])
		{
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '\'')
				i++;
			tokenizer->commands[cmd_i++] = strndup(&line[start], i - start);
		}
	}
	tokenizer->commands[cmd_i] = NULL;
	return (1);
}

void init_lexer(t_infos *infos, char *line, t_tokenizer *tokenizer)
{
	int len = ft_strlen(line);

	len = ft_strlen(line);
	if (ft_strchr(line, '|'))
		it_is_pipe(line, tokenizer);
	tokenizer->commands = malloc(sizeof(char *) * (len / 2 + 2));
	if (handle_quotes(line, tokenizer) == 0)
	{
		printf("minishell: syntax error near unexpected quote `\''\n");
		return ;
	}
	execute_commands(tokenizer, infos);
}
