/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/23 10:46:30 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:27:00 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	if (num == 0)
		return (0);
	while (i < num && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (i < num)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}

/*
int	main(void)
{
	char	*str1;
	char	*str2;

	str1 = "aihaho";
	str2 = "azaia";
	printf(" Now as thou can see the comparaison be\
	tween them is like %d", ft_strncmp(str1, str2, 2));
	return (0);
}
*/
