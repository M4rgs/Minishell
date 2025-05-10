/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:26:53 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/11 00:46:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <wait.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include "readline/readline.h"
# include "readline/history.h"

# define WHITE "\001\033[1;37m\002"
# define RESET "\001\033[0m\002"

typedef struct s_envinfo{
	char	**env;
}	t_envinfo;

typedef struct s_tokenizer{
	char	**commands;
} t_tokenizer;

typedef struct s_infos{
	t_envinfo	*envp_info;
	char		*prom;
}	t_infos;

char	*generate_prompt(void);
void    init_lexer(t_infos *infos, char *line, t_tokenizer *tokenizer);

#endif