/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/23 10:48:53 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:24:41 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*string;
	size_t				i;

	string = (const unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (string[i] == (unsigned char)c)
			return ((void *)(string + i));
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	const char	*testStr = "Hello, World!";
	char		ch;
	char		*result;
	char		notFoundCh;
	const char	*shortStr = "abcde";

	ch = 'W';
	size_t n = 13; // Length of the string including null terminator
	// Test 1: Character found
	result = ft_memchr(testStr, ch, n);
	if (result)
	{
		printf("Character '%c' found at position: %ld\n", ch, result
			- testStr);
	}
	else
	{
		printf("Character '%c' not found in the string.\n", ch);
	}
	// Test 2: Character not found
	notFoundCh = 'X';
	result = ft_memchr(testStr, notFoundCh, n);
	if (result)
	{
		printf("Character '%c' found at position: %ld\n", notFoundCh, result
			- testStr);
	}
	else
	{
		printf("Character '%c' not found in the string.\n", notFoundCh);
	}
	// Test 3: Searching up to a specific number of bytes
	result = ft_memchr(shortStr, 'c', 3); // Search within first 3 bytes
	if (result)
	{
		printf("Character 'c' found within the first 3 bytes at position:
			%ld\n", result - shortStr);
	}
	else
	{
		printf("Character 'c' not found within the first 3 bytes.\n");
	}
	return (0);
}
*/