/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:18 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/17 04:18:35 by tamounir         ###   ########.fr       */
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
			return (ft_putstr_fd(PIPE_ERR, 2), 1);
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
	tokenizer->commands = ft_malloc((sizeof(char *) * (len + 1)), 1);
	if (!tokenizer->commands)
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
	if (has_heredoc(line) == 1)
		tokenizer->is_heredoc = 1;
	if (!tokenize_line(line, tokenizer))
		return ;
	if (tokenizer->is_heredoc == 0)
		expand_all_tokens(tokenizer, infos->envp_info->env);
	execute_commands(tokenizer, infos);
}
