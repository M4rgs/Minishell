/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:59:33 by tamounir          #+#    #+#             */
/*   Updated: 2024/11/03 17:01:43 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	dgts(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			counts;
	char		*p;
	long int	num;

	counts = dgts(n);
	num = n;
	p = malloc(counts + 1);
	if (!p)
		return (NULL);
	p[counts] = '\0';
	if (n < 0)
	{
		p[0] = '-';
		num = -num;
	}
	while (counts > 0 && num != 0)
	{
		p[counts - 1] = num % 10 + '0';
		num = num / 10;
		counts--;
	}
	if (n == 0)
		p[0] = '0';
	return (p);
}
