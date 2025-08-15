/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_unquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:46:47 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_unquoted_token(char *line, int *i)
{
	int		start;

	start = *i;
	while (line[*i] && !is_whitespace(line[*i])
		&& line[*i] != '\'' && line[*i] != '"')
	{
		if (line[*i] == '$' && (line[*i + 1] != '\'' \
			&& line[*i + 1] != '"'))
			line[*i] = '$' - 100;
		(*i)++;
	}
	return (ft_substr(line, start, *i - start));
}

char	*extract_quoted_token(char *line, int *i, \
	t_tokenizer *tokenizer, int token_index)
{
	int		start;
	char	quote;
	char	*token;

	if (line[*i] == '"' && ft_strncmp(line + *i, "\"$\"", 3) != 0)
		line = change_to_inpren(line);
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
		return (handle_unmatched_quote(quote));
	token = ft_substr(line, start, *i - start);
	(*i)++;
	tokenizer->was_quoted[token_index] = 1;
	return (token);
}

char	*extract_token(char *line, int *i, \
	t_tokenizer *tokenizer, int token_index)
{
	char	*token;
	char	*part;

	token = ft_strdup("");
	while (line[*i] && !is_whitespace(line[*i]))
	{
		if (line[*i] == '$' && (line[*i + 1] == '"' || line[*i + 1] == '\''))
		{
			(*i)++;
			continue ;
		}
		if (line[*i] == '"' || line[*i] == '\'')
			part = extract_quoted_token(line, i, tokenizer, token_index);
		else
			part = extract_unquoted_token(line, i);
		if (!part)
		{
			return (NULL);
			break ;
		}
		token = ft_strjoin(token, part);
	}
	return (token);
}
