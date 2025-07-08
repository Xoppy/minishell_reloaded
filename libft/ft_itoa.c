/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:10:59 by cauffret          #+#    #+#             */
/*   Updated: 2024/10/31 01:57:01 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lengthy(int n)
{
	int	i;

	i = 0;
	if (n == INT_MIN)
		return (10);
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		size;
	long	nb;
	char	*dest;

	nb = n;
	size = (ft_lengthy(n) + (n < 0));
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	if (n < 0)
	{
		dest[0] = '-';
		nb = -nb;
	}
	dest[size] = '\0';
	size--;
	while (size >= (n < 0))
	{
		dest[size] = (nb % 10) + 48;
		nb = nb / 10;
		size--;
	}
	return (dest);
}
