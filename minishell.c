/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:27:53 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/17 06:38:49 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

volatile sig_atomic_t	g_signal_flag = 0;

char	**ft_envinit(char **envp)
{
	int		i;
	char	**s;

	i = 0;
	while (envp[i])
		i++;
	s = ft_malloc((sizeof(char *) * (i + 1)), 1);
	s[i] = NULL;
	while (i--)
		s[i] = ft_strdup(envp[i]);
	return (s);
}

void	init_struct(t_infos *infos, char **envp, t_tokenizer *tokenizer)
{
	infos->envp_info = ft_malloc(sizeof(t_envinfo), 1);
	infos->prom = NULL;
	if (!envp[0])
		infos->envp_info->env = default_env();
	else
		infos->envp_info->env = ft_envinit(envp);
	tokenizer->is_heredoc = 0;
	tokenizer->itispipe = 0;
	tokenizer->infos = infos;
	tokenizer->was_quoted = ft_calloc(MAX_ALLOC, sizeof(int));
	infos->prom = generate_prompt(infos->envp_info->env);
}

char	*generate_prompt(char **env)
{
	char	*usr;
	char	*usr_p;
	char	*promt;

	usr = get_env_value(env, "USER");
	if (!usr)
		usr = "unknown";
	usr_p = ft_strjoin(usr, "@");
	promt = ft_strjoin(usr_p, WHITE "Minishell:~$ " RESET);
	return (promt);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_infos		infos;
	t_tokenizer	tokenizer;

	(void)ac;
	(void)av;
	signal(SIGINT, signal_handling);
	signal(SIGQUIT, SIG_IGN);
	init_struct(&infos, envp, &tokenizer);
	while (1)
	{
		input = readline(infos.prom);
		if (!input)
			ft_exit(NULL);
		if (*input)
			add_history(input);
		init_tokenizer(&infos, input, &tokenizer);
		ft_memset(tokenizer.was_quoted, 0, MAX_ALLOC * sizeof(int));
		free(input);
	}
	ft_malloc(0, 0);
}
