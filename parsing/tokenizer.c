/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:18 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/18 23:18:48 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_token(char *line, int *i, int *cmd_i, t_tokenizer *tokenizer)
{
	char	*token;

	token = extract_token(line, i, tokenizer);
	if (!token)
		return (1);
	if (ft_strcmp(token, "|") == 0)
	{
		if (*cmd_i == 0 || !line[*i])
		{
			g_last_exit_status = 258;
			return (ft_putstr_fd(PIPE_ERR, 2), 1);
		}
	}
	tokenizer->commands[*cmd_i] = token;
	(*cmd_i)++;
	return (0);
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
		printf("bash: .: filename argument required\n.: usage: . filename [arguments]\n");
		g_last_exit_status = 2;
		return ;
	}
	if (has_heredoc(line) == 1)
		tokenizer->is_heredoc = 1;
	if (!tokenize_line(line, tokenizer))
		return ;
	if (tokenizer->is_heredoc == 0)
		expand_all_tokens(tokenizer, infos->envp_info->env);
	execute_commands(tokenizer, infos);
}
