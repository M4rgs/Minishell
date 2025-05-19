/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:18 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/19 05:33:17 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_pipe_token(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (1);
	return (0);
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

char	*extract_quoted_token(char *line, int *i)
{
	int		start;
	int		len;
	char	quote;
	char	*token;

	quote = line[(*i)++];
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] != quote || (*i - start == 0))
	{
		printf(QUOTE_ERR, quote);
		return (NULL);
	}
	len = *i - start;
	token = ft_substr(line, start, len);
	(*i)++;
	return (token);
}

char	*extract_token(char *line, int *i)
{
	while (is_whitespace(line[*i]))
		(*i)++;
	if (line[*i] == '\'' || line[*i] == '"')
		return (extract_quoted_token(line, i));
	else
		return (extract_unquoted_token(line, i));
}

int	handle_syntax_error(char **cmds, int count, char *token)
{
	int	i;

	i = 0;
	if (token)
		free(token);
	while (i < count)
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
	return (0);
}

int	init_tokenizer_array(t_tokenizer *tokenizer, int len)
{
	tokenizer->commands = malloc(sizeof(char *) * (len + 1));
	if (!tokenizer->commands)
		return (0);
	return (1);
}

int	process_token(char *line, int *i, int *cmd_i, t_tokenizer *tokenizer)
{
	char	*token;

	token = extract_token(line, i);
	if (!token)
		return (handle_syntax_error(tokenizer->commands, *cmd_i, NULL));
	if (is_pipe_token(token))
	{
		if (*cmd_i == 0 || !line[*i])
		{
			ft_putstr_fd(PIPE_ERR, 2);
			return (handle_syntax_error(tokenizer->commands, *cmd_i, token));
		}
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
	if (!init_tokenizer_array(tokenizer, len))
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
	if (!tokenize_line(line, tokenizer))
		return ;
	execute_commands(tokenizer, infos);
}
