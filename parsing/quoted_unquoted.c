/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_unquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:46:47 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/22 08:23:23 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_unquoted_token(char *line, int *i)
{
	int		start;

	start = *i;
	while (line[*i] && !is_whitespace(line[*i])
		&& line[*i] != '\'' && line[*i] != '"' && line[*i] != '|')
		(*i)++;
	return ft_substr(line, start, *i - start);
}

char	*extract_quoted_token(char *line, int *i, t_tokenizer *tokenizer)
{
	int		start;
	int		len;
	char	quote;
	char	*token;

	if (line[*i] == '$' && (line[*i + 1] == '"' || line[*i + 1] == '\''))
		(*i)++;
	if (line[*i] != '"' && line[*i] != '\'')
		return (NULL);
	quote = line[(*i)++];
	start = *i;
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '<' && line[*i + 1] == '<')
			tokenizer->is_heredoc = 0;
		(*i)++;
	}
	if (line[*i] != quote)
	{
		printf("Syntax error: unmatched %c\n", quote);
		g_last_exit_status = 258;
		return (NULL);
	}
	len = *i - start;
	token = ft_substr(line, start, len);
	(*i)++;
	return (token);
}

char	*extract_token(char *line, int *i, t_tokenizer *tokenizer)
{
	char	*token;
	char	*part;

	token = ft_strdup("");
	while (line[*i] && !is_whitespace(line[*i]) && line[*i] != '|')
	{
		if (line[*i] == '"' || line[*i] == '\'')
			part = extract_quoted_token(line, i, tokenizer);
		else
			part = extract_unquoted_token(line, i);
		if (!part)
			break;
		token = ft_strjoin(token, part);
	}
	return (token);
}


/*char	*extract_quoted_token(char *line, int *i, t_tokenizer *tokenizer)
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
			g_last_exit_status = 258;
			return (NULL);
		}
		len = *i - start;
		token = ft_substr(line, start, len);
		(*i)++;
		return (token);
	}
	if (line[*i] == '$' && (line[*i + 1] == '"' || line[*i + 1] == '\''))
	{
		quote = line[*i + 1];
		*i += 2;
		start = *i;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] != quote)
		{
			printf("Syntax error: unmatched %c\n", quote);
			g_last_exit_status = 258;
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
		{
			if (line[*i] == '<' && line[*i + 1] == '<')
				tokenizer->is_heredoc = 0;
			(*i)++;
		}
		if (line[*i] != quote)
		{
			printf("Syntax error: unmatched %c\n", quote);
			g_last_exit_status = 258;
			return (NULL);
		}
		len = *i - start;
		token = ft_substr(line, start, len);
		(*i)++;
		return (token);
	}
	return (NULL);
}
*/