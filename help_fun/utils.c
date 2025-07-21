/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:31:40 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/21 13:01:31 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	return (res);
}

int	get_env_index(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_delimiter_has_quote(char *s)
{
	int	i;

	i = 0;
	while (is_whitespace(s[i]))
		i++;
	if (s[i] == '\'' || s[i] == '"')
		return (1);
	return (0);
}

int	has_heredoc(char *line, t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			if (is_delimiter_has_quote(line + i + 2) == 0)
				tokenizer->has_to_expand = 1;
			else
				tokenizer->has_to_expand = 0;
			return (1);
		}
		i++;
	}
	return (0);
}
