/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamounir <tamounir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 00:14:26 by tamounir          #+#    #+#             */
/*   Updated: 2024/11/03 01:30:58 by tamounir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
			result++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (result);
}

static char	*allo_words(const char *s, char c)
{
	size_t	len;
	char	*result;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		len++;
	}
	result = (char *)malloc(sizeof(char) * (len +1));
	if (!result)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		result[len] = s[len];
		len++;
	}
	result[len] = '\0';
	return (result);
}

static char	**ft_free(char **words, size_t index)
{
	size_t	i;

	i = 0;
	while (index > i)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < count)
	{
		while (s[i] && s[i] == c)
			i++;
		result[j] = allo_words(&s[i], c);
		if (!result[j])
			return (ft_free(result, j));
		while (s[i] && s[i] != c)
			i++;
	}
	result[count] = NULL;
	return (result);
}
