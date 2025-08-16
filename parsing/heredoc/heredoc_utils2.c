/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:31:47 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/16 01:30:56 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_heredoc_index(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], "<<") == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**handle_heredoc_syntax_error(void)
{
	exit_status_value(258, 1);
	ft_putstr_fd(NEWL_ERR, 2);
	return (NULL);
}

void	ft_signheredoc(int sig)
{
	if (sig == SIGINT)
		exit(1);
}
