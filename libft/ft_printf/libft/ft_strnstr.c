/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/23 11:16:58 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:27:49 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

size_t	ft_strlen(const char *str);

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s2_len;

	i = 0;
	s2_len = ft_strlen(s2);
	if (*s2 == 0)
		return ((char *)s1);
	while (s1[i] != 0 && (i + s2_len) <= len)
	{
		j = 0;
		while (s1[i + j] == s2[j] && s2[j] != 0)
			j++;
		if (j == s2_len)
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
/*
int main (void)
{
	char	test1[] = "Hello this is John.";
	char	test2[] = "John";

	printf("Return value is: %s", ft_strnstr(test1,test2,20));
}
*/
// Need to redo this, i don't have the i+j thingy yet printed in my mind.