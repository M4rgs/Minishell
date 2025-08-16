/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:26:53 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/16 05:32:28 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include <limits.h>

# define WHITE "\001\033[1;37m\002"
# define RESET "\001\033[0m\002"
# define PIPE_ERR "minishell: syntax error near unexpected token `|`\n"
# define CD_ERR "minishell: cd: PATH not set\n"
# define EXIT_ERR_NU "minishell: exit: too many arguments\n"
# define CMD_NOT_FND "Minishell: command not found\n"
# define NEWL_ERR "Minishell: syntax error near unexpected token `newline'\n"

# define MAX_ALLOC 500000

extern volatile sig_atomic_t	g_signal_flag;

typedef struct s_infos			t_infos;
typedef struct s_tokenizer		t_tokenizer;

typedef struct s_envinfo
{
	char	**env;
}	t_envinfo;

typedef struct s_pipe_tokenizer
{
	char		***pipe_commands;
	int			cmds_allocated;
	int			i;
	int			cmd_i;
	int			start;
	int			end;
	int			*pipefds;
	int			cmd_count;
	t_tokenizer	*tokenizer;
}	t_pipe_tokenizer;

typedef struct s_tokenizer
{
	char	**commands;
	int		is_heredoc;
	int		has_to_expand_here;
	int		*was_quoted;
	int		itispipe;
	t_infos	*infos;
}	t_tokenizer;

typedef struct s_infos
{
	t_envinfo	*envp_info;
	t_tokenizer	*tokenizer;
	char		*prom;
}	t_infos;

typedef struct s_fds
{
	int	in;
	int	out;
	int	is_pipe;
}		t_fds;

typedef struct s_wilddata
{
	char	**new_cmds;
	char	**cmds;
	char	**matches;
	int		idx;
	int		count;
	int		old_len;
}	t_wilddata;

/*-----------HELPER-----------*/
char	*generate_prompt(char **env);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
int		is_whitespace(char c);
char	*ft_strjoin_char(char *s, char c);
int		is_valid_identifier(const char *arg, int flag);
void	heredoc_child(int fd, char *delimiter, \
	char **env, t_tokenizer *tokenizer);
int		count_cmds(char **cmds, int heredoc_index);
void	copy_cmds(char **cmds, char **new_cmds, int heredoc_index);
void	remove_empty_args(char **args, t_tokenizer *tokenizer);
void	trunc_expanded_spaces(char ***new_cmds, char *expanded, int *k);
char	*handle_dollar(char *str, int *i, char **env, char *result);
char	*exit_status_expanding(char *rzlt, int *i);
char	*ft_strjoin_char(char *s, char c);
char	*expand_env_var(const char *str, int *i_ptr, char **env, char *result);
char	*handle_unmatched_quote(char quote);
char	*change_to_inpren(char *line);
char	*create_env_entry(char **env, char *key, char *value, int append);
int		is_valid_identifier(const char *arg, int flag);
int		find_env_index(char **env, char *key);
int		is_delimiter_has_quote(char *s);
int		find_heredoc_index(char **cmds);
char	**handle_heredoc_syntax_error(void);
int		exit_status_value(int value, int flag);
void	restore_std_fds(int saved_stdout, int saved_stdin);
int		save_std_fds(int *saved_stdout, int *saved_stdin);
char	*new_line_tokenized(char *line);
int		is_double_operator(char c1, char c2);
int		is_operator_char(char c);
int		ft_isdigit_string(char *c);
int		insert_new_env(char ***env, char *new_entry);
void	non_numeric_exit(char **splitted);
int		ft_atol(const char *str, long *out);
void	fill_new_cmds(t_wilddata *d);
int		tokens_length(char **tokens);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strndup(const char *s, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
void	ft_signheredoc(int sig);
void	*ft_malloc(size_t size, int flag);
char	**ft_split(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	print_error(char *cmd, char *msg);
void	signal_handling(int sig);
int		update_env_entry(char ***env, char *key, char *value, int append);
/*-----------HELPER-----------*/

/*-----------PARSING-----------*/
char	**default_env(void);
void	init_tokenizer(t_infos *infos, char *line, t_tokenizer *tokenizer);
char	*extract_token(char *line, int *i, \
	t_tokenizer *tokenizer, int token_index);
char	*expand_vars_in_string(char *str, char **env, t_tokenizer *tokenizer);
char	*extract_unquoted_token(char *line, int *i);
char	*extract_quoted_token(char *line, int *i, \
	t_tokenizer *tokenizer, int token_index);
char	*find_path_env(char **envp);
void	expand_all_tokens(t_tokenizer *tokenizer, char **env, char *line);
int		has_heredoc(char *line, t_tokenizer *tokenizer);
int		get_env_index(char **env, const char *key);
char	*get_env_value(char **env, const char *key);
int		validate_syntax(t_tokenizer *tokenizer);
int		redir_syntax_err(char **cmd, int indexx);
void	wildcard_expand_tokens(char ***cmds_ptr, t_tokenizer *tokenizer);
/*-----------PARSING-----------*/

/*-----------EXECUTION-----------*/
int		ft_heredoc_init(char **cmds, char **env, t_tokenizer *tokenizer);
char	*get_command_path(char *cmd, char **envp);
int		check_command_path(char *cmd, char **path);
void	execute_commands(t_tokenizer *tokenizer, t_infos *infos);
/*-----------EXECUTION-----------*/

/*-----------REDIRECTIONS-----------*/
char	**new_cmds_no_redi(char **args);
void	check_redirectons(char ***args);
/*-----------REDIRECTIONS-----------*/

/*-----------PIPES-----------*/
void	it_is_pipe(char **env, t_tokenizer *tokenizer);
void	check_redirectons(char ***args);
int		count_pipes(char **tokens);
char	**copy_command_range(char **commands, int start, int end);
void	setup_pipe_fds(t_pipe_tokenizer *pt);
void	exec_pipe_command(t_pipe_tokenizer *pt, \
	char ***pipe_commands, char **env);
void	process_all_heredocs(char ***pipe_commands, \
	char **env, t_tokenizer *tokenizer);
/*-----------PIPES-----------*/

/*-----------BUILTINS-----------*/
int		check_builtings(char **args, char ***env, int is_pipe);
int		check_builtin_pwd(char **args, char ***env, t_fds fds);
int		handle_unset_builtin(char **args, char ***env, t_fds fds);
int		handle_export_builtin(char **args, char ***env, t_fds fds);
int		handle_cd_builtin(char **args, char ***env, t_fds fds);
int		handle_exit_builtin(char **args, t_fds fds);
int		builtin_echo(int l, char **cmds);
int		builtin_pwd(char **env);
void	ft_exit(char **args);
void	builting_export_only(char **env);
int		builtin_export(char ***env, char **args);
int		builtin_unset(char ***env, char **args);
void	builti_cd(char ***env, char **args);
int		builtin_env(char **env);
/*-----------BUILTINS-----------*/

#endif