/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 04:18:09 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/19 02:50:49 by tamounir         ###   ########.fr       */
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
	return (tmp);
}

char *expand_vars_in_string(char *str, char **env)
{
	int		i;
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	i = 0;
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
				tmp = ft_strjoin_char(result, '$');
				result = tmp;
			}
		}
		else
		{
			tmp = ft_strjoin_char(result, str[i]);
			result = tmp;
			i++;
		}
	}
	if (!*result)
		return (NULL);
	return (result);
}




void expand_all_tokens(t_tokenizer *tokenizer, char **env, char *line)
{
	int		i;
	int		j;
	int		k;
	char	**new_cmds;
	char	*expanded, **split;
	
	i = 0;
	j = 0;
	k = 0;
	new_cmds  = ft_malloc((sizeof(char *) * (ft_strlen(line) + 1)), 1);
	while (tokenizer->commands[i])
	{
		if (tokenizer->commands[0] && ft_strcmp(tokenizer->commands[0], "export") == 0)
			return;
		expanded = expand_vars_in_string(tokenizer->commands[i], env);
		if (expanded && ft_strchr(expanded, ' '))
		{
			split = ft_split(expanded, ' ');
			j = 0;
			while (split[j])
			{
				new_cmds[k++] = ft_strdup(split[j]);
				j++;
			}
			free(expanded);
		}
		else
		{
			new_cmds[k++] = expanded;
		}
		i++;
	}
	new_cmds[k] = NULL;
	tokenizer->commands = new_cmds;
}
