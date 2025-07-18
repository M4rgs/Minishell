/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 04:18:09 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/17 04:30:34 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_char(char *s, char c)
{
	char tmp[2] = {c, 0};
	return ft_strjoin(s, tmp);
}

char *exit_status_expanding(char *rzlt, int *i)
{
	char	*exit_string = ft_itoa(g_last_exit_status);
	char	*tmp = ft_strjoin(rzlt, exit_string);
	(*i)++;
	return (tmp);
}

char *expand_env_var(const char *str, int *i_ptr, char **env, char *result)
{
	int		start = *i_ptr;
	char	*var_name;
	char	*value;
	char	*tmp;

	while (ft_isalnum(str[*i_ptr]) || str[*i_ptr] == '_')
		(*i_ptr)++;
	var_name = ft_substr(str, start, *i_ptr - start);
	value = get_env_value(env, var_name);
	free(var_name);
	if (!value)
		value = ft_strdup("");
	tmp = ft_strjoin(result, value);
	return tmp;
}

char *expand_vars_in_string(char *str, char **env)
{
	int		i = 0;
	char	*result = ft_strdup("");

	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				result = exit_status_expanding(result, &i);
			else if (ft_isalnum(str[i]) || str[i] == '_')
				result = expand_env_var(str, &i, env, result);
			else
			{
				char *tmp = ft_strjoin_char(result, '$');
				result = tmp;
			}
		}
		else
		{
			char *tmp = ft_strjoin_char(result, str[i]);
			result = tmp;
			i++;
		}
	}
	return result;
}

void	expand_all_tokens(t_tokenizer *tokenizer, char **env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokenizer->commands && tokenizer->commands[i])
	{
		expanded = expand_vars_in_string(tokenizer->commands[i], env);
		tokenizer->commands[i] = expanded;
		i++;
	}
}