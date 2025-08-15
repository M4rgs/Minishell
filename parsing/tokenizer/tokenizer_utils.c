/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:29:19 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_syntax_err(char **cmd, int indexx)
{
	if (cmd[indexx + 1] && (
			ft_strcmp(cmd[indexx + 1], "|") == 0
			|| ft_strcmp(cmd[indexx + 1], "<") == 0
			|| ft_strcmp(cmd[indexx + 1], ">") == 0
			|| ft_strcmp(cmd[indexx + 1], "<<") == 0
			|| ft_strcmp(cmd[indexx + 1], ">>") == 0))
	{
		print_error(cmd[indexx + 1], \
			"bash: syntax error near unexpected token `\n");
		exit_status_value(2, 1);
		return (1);
	}
	return (0);
}

static void	update_quote_state(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (!*quote)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
}

static int	handle_single_operator(char *line, char **new_line, int i)
{
	if (i > 0 && !is_whitespace(line[i - 1]))
		*new_line = ft_strjoin(*new_line, " ");
	*new_line = ft_strjoin(*new_line, ft_strndup(&line[i], 1));
	if (line[i + 1] && !is_whitespace(line[i + 1]))
		*new_line = ft_strjoin(*new_line, " ");
	return (1);
}

static int	handle_double_operator(char *line, char **new_line, int i)
{
	if (i > 0 && !is_whitespace(line[i - 1]))
		*new_line = ft_strjoin(*new_line, " ");
	*new_line = ft_strjoin(*new_line, ft_strndup(&line[i], 2));
	if (line[i + 2] && !is_whitespace(line[i + 2]))
		*new_line = ft_strjoin(*new_line, " ");
	return (2);
}

char	*new_line_tokenized(char *line)
{
	int		i;
	char	*new_line;
	char	quote;

	i = 0;
	quote = 0;
	new_line = ft_strdup("");
	while (line[i])
	{
		update_quote_state(line[i], &quote);
		if (!quote && is_double_operator(line[i], line[i + 1]))
		{
			i += handle_double_operator(line, &new_line, i);
			continue ;
		}
		if (!quote && is_operator_char(line[i]))
		{
			i += handle_single_operator(line, &new_line, i);
			continue ;
		}
		new_line = ft_strjoin(new_line, ft_strndup(&line[i], 1));
		i++;
	}
	return (new_line);
}
