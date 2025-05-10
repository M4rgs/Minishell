/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:53:11 by tamounir          #+#    #+#             */
/*   Updated: 2024/10/27 20:47:59 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		odd;
	size_t	rzlt;

	i = 0;
	odd = 1;
	rzlt = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			odd = odd * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rzlt = rzlt * 10 + (str[i] - 48);
		if (rzlt > 9223372036854775807 && odd == -1)
			return (0);
		if (rzlt > 9223372036854775807 && odd == 1)
			return (-1);
		i++;
	}
	return (rzlt * odd);
}
