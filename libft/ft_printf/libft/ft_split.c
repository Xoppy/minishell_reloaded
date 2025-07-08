/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/24 15:36:04 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:24:55 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *destination, const char *source, size_t num)
{
	size_t	i;

	i = 0;
	if (destination == NULL)
		return (NULL);
	while (i != num && source[i] != 0)
	{
		destination[i] = source[i];
		i++;
	}
	while (i != num)
	{
		destination[i] = 0;
		i++;
	}
	return (destination);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_strncpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_dup_word(const char **s, char c)
{
	const char	*start;
	size_t		len;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	len = *s - start;
	return (ft_strndup(start, len));
}

char	**ft_split(char const *s, char c)
{
	size_t	num_words;
	size_t	i;
	char	**result;

	num_words = 0;
	i = 0;
	num_words = ft_count_words(s, c);
	result = (char **)malloc((num_words + 1) * sizeof(char *));
	while (*s)
	{
		if (*s != c)
		{
			result[i] = ft_dup_word(&s, c);
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
