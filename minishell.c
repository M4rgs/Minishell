/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:27:53 by tamounir          #+#    #+#             */
/*   Updated: 2025/05/11 00:28:24 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_envinit(char **envp)
{
	int		i;
	char	**s;

	i = 0;
	while (envp[i])
		i++;
	s = malloc(sizeof(char *) * (i + 1));
	s[i] = NULL;
	while (i--)
	{
		s[i] = ft_strdup(envp[i]);
	}
	return (s);
}

void	init_struct(t_infos *infos, char **envp)
{
	infos->prom = NULL;
	infos->envp_info = malloc(sizeof(t_envinfo));
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
	free(usr_p);
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
	char	*input;
	t_infos	infos;
	t_tokenizer tokenizer;
	signal(SIGINT, signal_handling);
	init_struct(&infos, envp);
	while (1)
	{
		infos.prom = generate_prompt();
		input = readline(infos.prom);
		free(infos.prom);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		init_lexer(&infos, input, &tokenizer);
		free(input);
	}
}
