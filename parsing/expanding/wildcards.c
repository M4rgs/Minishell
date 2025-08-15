/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 00:52:20 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	new_matches(char ***cmds_ptr, int idx, char **matches, int count)
{
	t_wilddata	d;

	d.cmds = *cmds_ptr;
	d.idx = idx;
	d.matches = matches;
	d.count = count;
	d.old_len = tokens_length(d.cmds);
	d.new_cmds = ft_malloc((d.old_len - 1 + count + 1) * sizeof(char *), 1);
	fill_new_cmds(&d);
	d.new_cmds[d.old_len - 1 + count] = NULL;
	*cmds_ptr = d.new_cmds;
}

int	wildcard_match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		if (wildcard_match(pattern + 1, str))
			return (1);
		if (*str && wildcard_match(pattern, str + 1))
			return (1);
		return (0);
	}
	if (*pattern == *str)
		return (wildcard_match(pattern + 1, str + 1));
	return (0);
}

static int	fill_matches(DIR *dir, const char *pattern,
		char **matches, int *count)
{
	struct dirent	*entry;
	int				size;

	size = 0;
	entry = readdir(dir);
	while (entry && size < 256)
	{
		if (wildcard_match(pattern, entry->d_name) == 1)
		{
			matches[size] = ft_strdup(entry->d_name);
			if (!matches[size])
			{
				*count = 0;
				return (0);
			}
			size++;
		}
		entry = readdir(dir);
	}
	matches[size] = NULL;
	*count = size;
	return (1);
}

char	**expand_wildcard(const char *pattern, int *count)
{
	static char	*matches[256 + 1];
	DIR			*dir;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		*count = 0;
		return (NULL);
	}
	if (!fill_matches(dir, pattern, matches, count))
	{
		closedir(dir);
		return (NULL);
	}
	closedir(dir);
	return (matches);
}

void	wildcard_expand_tokens(char ***cmds_ptr, t_tokenizer *tokenizer)
{
	char	**cmds;
	int		i;
	int		count;
	char	**matches;

	cmds = *cmds_ptr;
	i = 0;
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], '*') && tokenizer->was_quoted[i] == 0)
		{
			matches = expand_wildcard(cmds[i], &count);
			if (count > 0)
			{
				new_matches(&cmds, i, matches, count);
				i += count;
				continue ;
			}
		}
		i++;
	}
	*cmds_ptr = cmds;
}
