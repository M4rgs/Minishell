/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:26:53 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/24 09:22:11 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "readline/readline.h"
# include "readline/history.h"

# define WHITE "\001\033[1;37m\002"
# define RESET "\001\033[0m\002"
# define PIPE_ERR "minishell: syntax error near unexpected token `|`\n"

typedef struct s_envinfo
{
	char	**env;
}	t_envinfo;

typedef struct s_tokenizer
{
	char	**commands;
	int		is_heredoc;
	int		has_to_expand;
}	t_tokenizer;

typedef struct s_infos
{
	t_envinfo	*envp_info;
	t_tokenizer	*tokenizer;
	char		*prom;
}	t_infos;

extern int	g_last_exit_status;

char	*generate_prompt(void);
void	init_tokenizer(t_infos *infos, char *line, t_tokenizer *tokenizer);
void	execute_commands(t_tokenizer *tokenizer, t_infos *infos);
int		builtin_export(t_infos *infos, char **args);
int		builtin_unset(t_infos *infos, char **args);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
int		get_env_index(char **env, const char *key);
int		is_whitespace(char c);
int		has_heredoc(char *line, t_tokenizer *tokenizer);
char	*extract_token(char *line, int *i, t_tokenizer *tokenizer);
char	*get_env_value(char **env, const char *key);
char	*extract_quoted_token(char *line, int *i, t_tokenizer *tokenizer);
char	*extract_unquoted_token(char *line, int *i);
char	**default_env(void);
char	*get_env_value(char **env, const char *key);
void	builting_export_only(char **env);
char	*find_path_env(char **envp);
int		ft_heredoc_init(char **cmds, t_infos *infos, t_tokenizer *tokenizer);
char	*get_command_path(char *cmd, char **envp);
void	expand_all_tokens(t_tokenizer *tokenizer, char **env, char *line);
char	*ft_strjoin_char(char *s, char c);
char	*expand_vars_in_string(char *str, char **env);
char	*to_change(char *str, char c, char b);
void	ft_exit(char *input);

#endif