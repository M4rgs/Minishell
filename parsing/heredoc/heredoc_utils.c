/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 04:01:19 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_has_to_expand(t_tokenizer *tokenizer, char *line, int *i)
{
	(*i) += 2;
	if (is_delimiter_has_quote(line + *i))
		tokenizer->has_to_expand_here = 0;
	else
		tokenizer->has_to_expand_here = 2;
	return (1);
}

int	has_heredoc(char *line, t_tokenizer *tokenizer)
{
	int		i;
	char	quote;
	int		in_quote;

	i = 0;
	in_quote = 0;
	while (line[i])
	{
		if (!in_quote && (line[i] == '\'' || line[i] == '"'))
		{
			quote = line[i];
			in_quote = 1;
		}
		else if (in_quote && line[i] == quote)
		{
			in_quote = 0;
			quote = '\0';
		}
		else if (!in_quote && line[i] == '<' && line[i + 1] == '<')
			return (is_has_to_expand(tokenizer, line, &i));
		i++;
	}
	return (0);
}

void	heredoc_child(int fd, char *delimiter, \
	char **env, t_tokenizer *tokenizer)
{
	char	*input;

	signal(SIGINT, ft_signheredoc);
	while (1)
	{
		input = readline(">> ");
		if (!input)
			break ;
		if (tokenizer->has_to_expand_here == 2)
		{
			input = expand_vars_in_string(input, env, tokenizer);
			if (input == NULL)
				input = ft_strdup("");
		}
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
	close(fd);
	exit(0);
}

int	count_cmds(char **cmds, int heredoc_index)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmds[i])
	{
		if (i != heredoc_index && i != heredoc_index + 1)
			count++;
		i++;
	}
	return (count);
}

void	copy_cmds(char **cmds, char **new_cmds, int heredoc_index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (i != heredoc_index && i != heredoc_index + 1)
			new_cmds[j++] = cmds[i];
		i++;
	}
	new_cmds[j] = NULL;
}
