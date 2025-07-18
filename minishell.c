/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:27:53 by tamounir          #+#    #+#             */
/*   Updated: 2025/07/18 03:28:25 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_last_exit_status = 0;

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

void	init_struct(t_infos *infos, char **envp)
{
	infos->envp_info = ft_malloc(sizeof(t_envinfo), 1);
	infos->prom = NULL;
	if (!envp[0])
		infos->envp_info->env = default_env();
	else
		infos->envp_info->env = ft_envinit(envp);
}

char	*generate_prompt(void)
{
	char	*usr;
	char	*usr_p;
	char	*promt;

	usr = getenv("USER");
	if (!usr)
		usr = "unknown";
	usr_p = ft_strjoin(usr, "@");
	promt = ft_strjoin(usr_p, WHITE "Minishell:~$ " RESET);
	return (promt);
}

void	signal_handling(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*input;
	t_infos	infos;
	t_tokenizer tokenizer;
	tokenizer.is_heredoc = 0;
	signal(SIGINT, signal_handling);
	init_struct(&infos, envp);
	while (1)
	{
		infos.prom = generate_prompt();
		input = readline(infos.prom);
		if (!input)
			break ;
		if (ft_strcmp(input, "exit") == 0)
		{
			ft_malloc(0, 0);
			exit(0);
		}
		if (*input)
			add_history(input);
		init_tokenizer(&infos, input, &tokenizer);
		free(input);
	}
}
