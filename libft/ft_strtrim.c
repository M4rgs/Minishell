/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:47:03 by tamounir          #+#    #+#             */
/*   Updated: 2024/11/04 10:40:28 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isvalid(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len;
	char const	*start;
	char const	*end;
	char		*p;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	end = s1 + ft_strlen(s1) - 1;
	start = s1;
	while (start && isvalid(*start, set))
		start++;
	while (end > start && isvalid(*end, set))
		end--;
	len = end - start + 1;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	ft_strlcpy(p, start, len + 1);
	p[len] = '\0';
	return (p);
}
