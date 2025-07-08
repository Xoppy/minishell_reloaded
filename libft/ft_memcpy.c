/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/02 10:41:44 by azaemeki13        #+#    #+#             */
/*   Updated: 2024/10/25 11:24:47 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <string.h>
// #include <stdio.h>

void	*ft_memcpy(void *destination, const void *source, size_t num)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*src;

	if (destination == NULL || source == NULL || num == 0)
		return (destination);
	dest = (unsigned char *)destination;
	src = (const unsigned char *)source;
	i = 0;
	while (i < num)
	{
		dest[i] = src[i];
		i++;
	}
	return (destination);
}
/*
int	main(void) {
	char src[] = "Hello, World!"; // Source string
	char dest[50];  // Destination buffer with enough space
	char dest2[50]; // For comparison with standard memcpy

	// Use ft_memcpy to copy data from src to dest
	ft_memcpy(dest, src, strlen(src) + 1); // +1 to include the null terminator

	// Use standard memcpy to copy data for comparison
	memcpy(dest2, src, strlen(src) + 1);

	// Print results
	printf("ft_memcpy result: %s\n", dest);
	printf("standard memcpy result: %s\n", dest2);

	// Check if both results are the same
	if (strcmp(dest, dest2) == 0) {
		printf("The ft_memcpy function works correctly.\n");
	} else {
		printf("The ft_memcpy function did not work correctly.\n");
	}
	return (0);
}
*/