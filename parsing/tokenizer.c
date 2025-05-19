/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:18 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/19 02:20:12 by tamounir         ###   ########.fr       */
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

char	*extract_token(char *line, int *i)
{
	int		start;
	int		len;
	char	quote;
	char	*token;

	quote = 0;
	while (is_whitespace(line[*i]))
		(*i)++;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[(*i)++];
		start = *i;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] != quote)
			return (printf("minishell: syntax error near unexpected quote `%c`\n", quote), NULL);
		len = *i - start;
		token = ft_substr(line, start, len);
		(*i)++;
	}
	else
	{
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
	}
	return (token);
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

int	tokenize_line(char *line, t_tokenizer *tokenizer)
{
	int		i;
	int		cmd_i;
	int		len;
	char	*token;

	i = 0;
	cmd_i = 0;
	len = ft_strlen(line);
	//if (token)
		//(free(token), token = NULL);
	tokenizer->commands = malloc(sizeof(char *) * (len + 1));
	if (!tokenizer->commands)
		return (0);
	while (line[i])
	{
		token = extract_token(line, &i);
		if (!token)
			return (handle_syntax_error(tokenizer->commands, cmd_i, NULL));
		if (is_pipe_token(token))
		{
			if (cmd_i == 0 || !line[i])
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|`\n", 2);
				return (handle_syntax_error(tokenizer->commands, cmd_i, token));
			}
		}
		tokenizer->commands[cmd_i] = token;
		cmd_i++;
	}
	tokenizer->commands[cmd_i] = NULL;
	return (1);
}

void init_tokenizer(t_infos *infos, char *line, t_tokenizer *tokenizer)
{
	if (!tokenize_line(line, tokenizer)) 
		return;
	execute_commands(tokenizer, infos);
}
