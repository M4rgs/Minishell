/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:24:05 by tamounir          #+#    #+#             */
/*   Updated: 2025/08/15 01:59:26 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_overflow(unsigned long result, int digit, int sign)
{
	if (result > (unsigned long)LONG_MAX / 10)
		return (1);
	if (result == (unsigned long)LONG_MAX / 10)
	{
		if (sign == 1 && digit > LONG_MAX % 10)
			return (1);
		if (sign == -1 && digit > (LONG_MAX % 10 + 1))
			return (1);
	}
	return (0);
}

static int	parse_digits(const char *str, long *out, int sign)
{
	unsigned long	result;
	int				digit;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (check_overflow(result, digit, sign))
			return (1);
		result = result * 10 + digit;
		str++;
	}
	if (sign == 1)
		*out = (long)result;
	else
		*out = -(long)result;
	return (0);
}

int	ft_atol(const char *str, long *out)
{
	int	sign;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (parse_digits(str, out, sign));
}

void	non_numeric_exit(char **splitted)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(splitted[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_malloc(0, 0);
	exit(255);
}

int	ft_isdigit_string(char *c)
{
	int		i;

	i = 0;
	while (c[i])
	{
		if ((c[i] < '0' || c[i] > '9') && c[i] != '+' && c[i] != '-')
			return (1);
		i++;
	}
	return (0);
}
