/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:18 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/24 03:38:51 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_heredoc(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

char	*get_env_value(char **env, const char *key)
{
	int	i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (ft_strdup(ft_strchr(env[i], '=') + 1));
		i++;
	}
	return (NULL);
}

char	*expand_vars_in_string(char *str, char **env)
{
	int		i = 0;
	char	*result = ft_strdup("");

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' ))
		{
			int		start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			char *var_name = ft_substr(str, start, i - start);
			char *value = get_env_value(env, var_name);
			if (!value)
				value = ft_strdup("");
			char *tmp = ft_strjoin(result, value);
			result = tmp;
		}
		else
		{
			char next[2] = {str[i++], 0};
			char *tmp = ft_strjoin(result, next);
			result = tmp;
		}
	}
	return (result);
}


void	expand_all_tokens(t_tokenizer *tokenizer, char **env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokenizer->commands && tokenizer->commands[i])
	{
		expanded = expand_vars_in_string(tokenizer->commands[i], env);
		tokenizer->commands[i] = expanded;
		i++;
	}
}

char	*extract_unquoted_token(char *line, int *i)
{
	int		start;
	int		len;
	char	*token;

	start = *i;
	while (line[*i] && !is_whitespace(line[*i])
		&& line[*i] != '|' && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	len = *i - start;
	if (len == 0 && line[*i] == '|')
	{
		token = ft_strdup("|");
		(*i)++;
	}
	else
		token = ft_substr(line, start, len);
	return (token);
}

char	*extract_quoted_token(char *line, int *i, t_tokenizer *tokenizer)
{
	int		start;
	int		len;
	char	quote;
	char	*token;

	if (tokenizer->is_heredoc == 1 && line[*i] == '$' &&
		(line[*i + 1] == '"' || line[*i + 1] == '\''))
	{
		quote = line[*i + 1];
		*i += 2;
		start = *i;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] != quote)
		{
			printf("Syntax error: unmatched %c\n", quote);
			return (NULL);
		}
		len = *i - start;
		token = ft_substr(line, start, len);
		(*i)++;
		return (token);
	}
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[(*i)++];
		start = *i;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] != quote)
		{
			printf("Syntax error: unmatched %c\n", quote);
			return (NULL);
		}
		len = *i - start;
		token = ft_substr(line, start, len);
		(*i)++;
		return (token);
	}
	return (NULL);
}

char	*extract_token(char *line, int *i, t_tokenizer *tokenizer)
{
	while (is_whitespace(line[*i]))
		(*i)++;
	if (line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
		return (extract_quoted_token(line, i, tokenizer));
	if (line[*i] == '\'' || line[*i] == '"')
		return (extract_quoted_token(line, i, tokenizer));

	return (extract_unquoted_token(line, i));
}

int	process_token(char *line, int *i, int *cmd_i, t_tokenizer *tokenizer)
{
	char	*token;

	token = extract_token(line, i, tokenizer);
	if (!token)
		return (1);
	if (ft_strcmp(token, "|") == 0)
	{
		if (*cmd_i == 0 || !line[*i])
			return (ft_putstr_fd(PIPE_ERR,2), 1);
	}
	tokenizer->commands[*cmd_i] = token;
	(*cmd_i)++;
	return (1);
}

int	tokenize_line(char *line, t_tokenizer *tokenizer)
{
	int	i;
	int	cmd_i;
	int	len;

	i = 0;
	cmd_i = 0;
	len = ft_strlen(line);
	tokenizer->commands = ft_malloc((sizeof(char *) * (len + 1)), 1);
	if (!tokenizer->commands)
		return (0);
	while (line[i])
	{
		if (!process_token(line, &i, &cmd_i, tokenizer))
			return (0);
	}
	tokenizer->commands[cmd_i] = NULL;
	return (1);
}

void	init_tokenizer(t_infos *infos, char *line, t_tokenizer *tokenizer)
{
	if (has_heredoc(line) == 1)
		tokenizer->is_heredoc = 1;
	if (!tokenize_line(line, tokenizer))
		return ;
	if (tokenizer->is_heredoc == 1)
		expand_all_tokens(tokenizer, infos->envp_info->env);
	execute_commands(tokenizer, infos);
}
