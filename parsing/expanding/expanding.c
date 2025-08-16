/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:22:43 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/16 02:34:51 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_env_var(const char *str, int *i_ptr, char **env, char *result)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*tmp;

	start = *i_ptr;
	while (ft_isalnum(str[*i_ptr]) || str[*i_ptr] == '_')
		(*i_ptr)++;
	var_name = ft_substr(str, start, *i_ptr - start);
	value = get_env_value(env, var_name);
	if (!value)
		value = ft_strdup("");
	tmp = ft_strjoin(result, value);
	return (tmp);
}

char	*expand_vars_in_string(char *str, char **env, t_tokenizer *tokenizer)
{
	int		i;
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && tokenizer->has_to_expand_here == 2)
		{
			result = handle_dollar(str, &i, env, result);
			continue ;
		}
		if (str[i] == '$' - 100)
			result = handle_dollar(str, &i, env, result);
		else
		{
			tmp = ft_strjoin_char(result, str[i]);
			result = tmp;
			i++;
		}
	}
	return (result);
}

void	expand_all_tokens(t_tokenizer *tokenizer, char **env, char *line)
{
	int		i;
	int		k;
	char	**new_cmds;
	char	*expanded;

	i = 0;
	k = 0;
	new_cmds = ft_malloc((sizeof(char *) * (ft_strlen(line) + 1)), 1);
	while (tokenizer->commands[i])
	{
		expanded = expand_vars_in_string(tokenizer->commands[i], \
			env, tokenizer);
		if (tokenizer->was_quoted[i])
			new_cmds[k++] = expanded;
		else if (expanded && ft_strchr(expanded, ' '))
			trunc_expanded_spaces(&new_cmds, expanded, &k);
		else
			new_cmds[k++] = expanded;
		i++;
	}
	new_cmds[k] = NULL;
	wildcard_expand_tokens(&new_cmds, tokenizer);
	tokenizer->commands = new_cmds;
	remove_empty_args(tokenizer->commands, tokenizer);
}
