/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/23 18:04:36 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:25:24 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			total_size;
	unsigned int	i;
	unsigned int	j;
	char			*final;

	i = 0;
	j = 0;
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	final = malloc(total_size * sizeof(char));
	while (s1[i] != 0)
	{
		final[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != 0)
	{
		final[j] = s2[i];
		j++;
		i++;
	}
	final[j] = '\0';
	return (final);
}
/*
int	main(void)
{
	const char test [] = "Hello inner demons ";
	const char test1 [] = "It's your boi.";
	printf("I joined this: %s", ft_strjoin(test, test1));
	return (0);
}
*/
