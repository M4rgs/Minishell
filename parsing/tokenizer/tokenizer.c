/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:18 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*build_token(char *line, int *i, t_tokenizer *tokenizer, int cmd_i)
{
	char	*token;
	char	*next;
	char	*combined;

	token = extract_token(line, i, tokenizer, cmd_i);
	if (!token)
		return (NULL);
	if (ft_strchr(token, '=') && token[ft_strlen(token) - 1] == '='
		&& (line[*i] == '"' || line[*i] == '\''))
	{
		next = extract_token(line, i, tokenizer, cmd_i);
		if (!next)
			return (NULL);
		combined = ft_strjoin(token, next);
		return (combined);
	}
	return (token);
}

static int	check_newline_error(int cmd_i, char *line, int i)
{
	if (cmd_i == 0 || !line[i])
	{
		exit_status_value(258, 1);
		ft_putstr_fd(NEWL_ERR, 2);
		return (1);
	}
	return (0);
}

static int	process_token(char *line, int *i, \
	int *cmd_i, t_tokenizer *tokenizer)
{
	char	*token;

	token = build_token(line, i, tokenizer, *cmd_i);
	if (!token)
		return (1);
	if (ft_strcmp(token, "|") == 0 && tokenizer->was_quoted[*cmd_i] == 0)
		tokenizer->itispipe = 1;
	if ((ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0)
		&& tokenizer->was_quoted[*cmd_i] == 0)
	{
		if (check_newline_error(*cmd_i, line, *i))
			return (1);
	}
	tokenizer->commands[(*cmd_i)++] = token;
	return (0);
}

static int	tokenize_line(char *line, t_tokenizer *tokenizer)
{
	int	i;
	int	cmd_i;
	int	len;

	i = 0;
	cmd_i = 0;
	len = ft_strlen(line);
	tokenizer->commands = ft_malloc((sizeof(char *) * (len + 1)), 1);
	line = new_line_tokenized(line);
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (process_token(line, &i, &cmd_i, tokenizer) == 1)
			return (0);
	}
	tokenizer->commands[cmd_i] = NULL;
	return (1);
}

void	init_tokenizer(t_infos *infos, char *line, t_tokenizer *tokenizer)
{
	if (ft_strcmp(line, ".") == 0)
	{
		exit_status_value(127, 1);
		ft_putstr_fd("bash: .: filename argument required\n.: \
			usage: . filename [arguments]\n", 2);
		return ;
	}
	if (has_heredoc(line, tokenizer) == 1)
		tokenizer->is_heredoc = 1;
	if (!tokenize_line(line, tokenizer))
		return ;
	if (validate_syntax(tokenizer))
		return ;
	if (tokenizer->is_heredoc == 0)
		expand_all_tokens(tokenizer, infos->envp_info->env, line);
	execute_commands(tokenizer, infos);
}
