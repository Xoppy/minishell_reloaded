/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/23 11:04:59 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:24:44 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char	*pointer1;
	const unsigned char	*pointer2;
	size_t				i;

	pointer1 = (const unsigned char *)ptr1;
	pointer2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < num)
	{
		if (pointer1[i] != pointer2[i])
			return (pointer1[i] - pointer2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[] = "Hello";
	char	str2[] = "Hello";
	char	str3[] = "World";
	char	str4[] = "Hello, World!";

	// Test 1: Identical strings
	printf("Comparing '%s' and '%s': %d\n", str1, str2, ft_memcmp(str1, str2,
			5));
	// Should return 0
	// Test 2: Different strings
	printf("Comparing '%s' and '%s': %d\n", str1, str3, ft_memcmp(str1, str3,
			5));
	// Should return -1
		// Test 3: Different strings, second is greater
		printf("Comparing '%s' and '%s': %d\n", str3, str1, ft_memcmp(str3,
				str1, 5));
	// Should return 1
	// Test 4: Different lengths (first string is a prefix)
	printf("Comparing '%s' and '%s': %d\n", str1, str4, ft_memcmp(str1, str4,
			5));
	// Should return 0 (equal up to 5 chars)
	// Test 5: Compare different lengths (not enough bytes to compare)
	printf("Comparing '%s' and '%s': %d\n", str1, str4, ft_memcmp(str1, str4,
			7));
	// Should return -1 (str1 is less)
		return (0);
}
*/