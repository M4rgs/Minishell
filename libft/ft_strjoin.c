/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:10:42 by tamounir          #+#    #+#             */
/*   Updated: 2024/11/02 20:37:42 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	lent;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	lent = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = malloc(lent);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, lent);
	ft_strlcat(p, s2, lent);
	return (p);
}
