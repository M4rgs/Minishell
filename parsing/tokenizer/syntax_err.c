/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:37:13 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	validate_pipe_first_last(t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (tokenizer->commands[i])
	{
		if (ft_strcmp(tokenizer->commands[i], "|") == 0 \
			&& tokenizer->was_quoted[i] == 0)
		{
			if (i == 0)
			{
				ft_putstr_fd(PIPE_ERR, 2);
				exit_status_value(2, 1);
				return (1);
			}
			if (!tokenizer->commands[i + 1])
			{
				ft_putstr_fd(PIPE_ERR, 2);
				exit_status_value(2, 1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	validate_pipe_double(t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (tokenizer->commands[i])
	{
		if (ft_strcmp(tokenizer->commands[i], "|") == 0 \
			&& tokenizer->was_quoted[i] == 0)
		{
			if (tokenizer->commands[i + 1] \
				&& ft_strcmp(tokenizer->commands[i + 1], "|") == 0
				&& tokenizer->was_quoted[i + 1] == 0)
			{
				ft_putstr_fd(PIPE_ERR, 2);
				exit_status_value(2, 1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	validate_redir_missing_next(t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (tokenizer->commands[i])
	{
		if ((ft_strcmp(tokenizer->commands[i], "<") == 0
				|| ft_strcmp(tokenizer->commands[i], ">") == 0
				|| ft_strcmp(tokenizer->commands[i], "<<") == 0
				|| ft_strcmp(tokenizer->commands[i], ">>") == 0)
			&& tokenizer->was_quoted[i] == 0)
		{
			if (!tokenizer->commands[i + 1])
			{
				ft_putstr_fd(PIPE_ERR, 2);
				exit_status_value(2, 1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	validate_redir_bad_next(t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (tokenizer->commands[i])
	{
		if ((ft_strcmp(tokenizer->commands[i], "<") == 0
				|| ft_strcmp(tokenizer->commands[i], ">") == 0
				|| ft_strcmp(tokenizer->commands[i], "<<") == 0
				|| ft_strcmp(tokenizer->commands[i], ">>") == 0)
			&& tokenizer->was_quoted[i] == 0)
		{
			if (redir_syntax_err(tokenizer->commands, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	validate_syntax(t_tokenizer *tokenizer)
{
	if (validate_pipe_first_last(tokenizer))
		return (1);
	if (validate_pipe_double(tokenizer))
		return (1);
	if (validate_redir_missing_next(tokenizer))
		return (1);
	if (validate_redir_bad_next(tokenizer))
		return (1);
	return (0);
}
