/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_unquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:46:47 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/18 03:44:29 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
