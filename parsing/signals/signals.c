/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:50:44 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/19 02:01:22 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_signals(void)
{
	disable_echoctl();
	signal(SIGINT, signal_handling);
	signal(SIGQUIT, signal_handling);
}
