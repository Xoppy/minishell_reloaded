/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/23 18:19:34 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:27:57 by cauffret         ###   ########.fr       */
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

static int	ft_isin(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimmed_str;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_isin(s1[start], set))
		start++;
	end = ft_strlen(s1);
	if (end == 0)
		return (ft_strdup(""));
	while (end > start && ft_isin(s1[end - 1], set))
		end--;
	len = end - start;
	trimmed_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!trimmed_str)
		return (NULL);
	ft_strncpy(trimmed_str, &s1[start], len);
	trimmed_str[len] = '\0';
	return (trimmed_str);
}

/*
int	main(void)
{
	char	s1[] = "  !!!Hello, World!!!  ";
	char	set[] = " !";
	char	*result;

	result = ft_strtrim(s1, set);
	if (result)
	{
		printf("Trimmed string: '%s'\n", result); // Output: 'Hello, World'
		free(result);
		// Free the allocated memory after use
	}
	return (0);
}
*/
