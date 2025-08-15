/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 04:20:55 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_unmatched_quote(char quote)
{
	exit_status_value(258, 1);
	ft_putstr_fd("Syntax error: unmatched ", 2);
	ft_putchar_fd(quote, 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

char	*change_to_inpren(char *line)
{
	char	*new_line;
	int		i;
	int		in_double_quote;

	i = 0;
	in_double_quote = 0;
	new_line = ft_malloc(ft_strlen(line) + 1, 1);
	while (line[i])
	{
		if (line[i] == '"')
			in_double_quote = !in_double_quote;
		if (line[i] == '$' && in_double_quote)
			new_line[i] = '$' - 100;
		else
			new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}
