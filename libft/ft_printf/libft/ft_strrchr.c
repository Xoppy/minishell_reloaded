/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/23 10:30:24 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:27:53 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*result;

	result = NULL;
	while (*s)
	{
		if (*s == (char)c)
			result = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)result);
}
/*
int main (void)
{
	const char	test[] = "Hello";

	printf("The last occurence of this char e is here: %s",
		(char*)ft_strrchr(test,'l'));
}
*/