/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/23 14:10:21 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:24:10 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*final;
	size_t	total_size;

	total_size = elementCount * elementSize;
	if (elementCount != 0 && SIZE_MAX / elementCount < elementSize)
		return (NULL);
	final = malloc(total_size);
	if (final == NULL)
		return (NULL);
	ft_memset(final, 0, total_size);
	return (final);
}
/*
int	main(void)
{
	char	*test;

	test = (char*)ft_calloc(5, sizeof(char));
	test ="abcd";
	printf("Test variable contains: %s", test);
	test = (char*)ft_calloc(5, sizeof(char));
	printf("Everything is set to 0 !: %s", test);
}
*/