/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/22 12:44:59 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:25:27 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

size_t	ft_strlen(const char *str);

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	size_t	remaining;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (n <= (dst_len))
		return (src_len + n);
	remaining = (n - dst_len - 1);
	while (i < remaining && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}
/*
int	main(void)
{
	char	test1[] = "Hello World";
	char	test2[10] = "abc";
	size_t	result;

	result = ft_strlcat(test2, test1, sizeof(test2));
	printf("My first append: %s\n", test2);
	printf("Is the result correct ? : %zu\n", result);
	return (0);
}
*/