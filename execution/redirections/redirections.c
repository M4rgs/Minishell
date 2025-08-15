/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:45:25 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	open_and_dup(int *fd, const char *file, int flags, int stdfd)
{
	*fd = open(file, flags, 0644);
	if (*fd < 0)
	{
		perror("Minishell");
		exit(1);
	}
	if (dup2(*fd, stdfd) == -1)
	{
		perror("dup2");
		close(*fd);
		exit(1);
	}
	close(*fd);
}

static int	handle_output_redirections(char **args, int *i)
{
	int	fd;

	if (ft_strcmp(args[*i], ">") == 0 && args[*i + 1])
	{
		open_and_dup(&fd, args[*i + 1], \
			O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		*i += 2;
		return (1);
	}
	if (ft_strcmp(args[*i], ">>") == 0 && args[*i + 1])
	{
		open_and_dup(&fd, args[*i + 1], \
			O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
		*i += 2;
		return (1);
	}
	return (0);
}

static int	handle_input_redirection(char **args, int *i)
{
	int	fd;

	if (ft_strcmp(args[*i], "<") == 0 && args[*i + 1])
	{
		open_and_dup(&fd, args[*i + 1], O_RDONLY, STDIN_FILENO);
		*i += 2;
		return (1);
	}
	return (0);
}

void	check_redirectons(char ***args)
{
	int		i;

	i = 0;
	while ((*args)[i])
	{
		if (handle_output_redirections(*args, &i))
			continue ;
		if (handle_input_redirection(*args, &i))
			continue ;
		i++;
	}
	*args = new_cmds_no_redi(*args);
	*args = new_cmds_no_redi(*args);
}
