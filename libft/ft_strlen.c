/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/21 10:53:49 by cauffret          #+#    #+#             */
/*   Updated: 2024/10/25 11:25:33 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

size_t	ft_strlen(const char *str)
{
	char	*nav;
	size_t	i;

	i = 0;
	nav = (char *)str;
	while (nav[i] != 0)
	{
		i++;
	}
	return (i);
}
/*
int main (void)
{
	char test [] = "Hello45544324";
	printf("The result is : %zu", ft_strlen(test));
	return (0);
}
*/