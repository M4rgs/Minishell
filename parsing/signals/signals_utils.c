/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:34:28 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/19 02:01:43 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static	void	handle_exec_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		exit_status_value(131, 1);
		return ;
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit_status_value(130, 1);
	}
}

static void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit_status_value(1, 1);
		g_signal_flag = 0;
	}
}

static void	handle_prompt_signal(int sig)
{
	if (sig == SIGINT)
	{
		exit_status_value(1, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handling(int sig)
{
	if (g_signal_flag == 2)
		handle_exec_signal(sig);
	else if (g_signal_flag == 1)
		handle_heredoc_signal(sig);
	else
		handle_prompt_signal(sig);
}
