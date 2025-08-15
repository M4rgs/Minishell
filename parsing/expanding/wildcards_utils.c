/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 02:11:41 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokens_length(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

static void	copy_before_idx(t_wilddata *d, int *i)
{
	while (*i < d->idx)
	{
		d->new_cmds[*i] = d->cmds[*i];
		(*i)++;
	}
}

static void	copy_matches(t_wilddata *d, int *i, int *j)
{
	while (*j < d->count)
	{
		d->new_cmds[*i + *j] = d->matches[*j];
		(*j)++;
	}
}

static void	copy_after_idx(t_wilddata *d, int k)
{
	while (k < d->old_len)
	{
		d->new_cmds[d->count + k - 1] = d->cmds[k];
		k++;
	}
}

void	fill_new_cmds(t_wilddata *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	copy_before_idx(d, &i);
	copy_matches(d, &i, &j);
	copy_after_idx(d, d->idx + 1);
}
