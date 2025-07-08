/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/16 14:18:59 by cauffret          #+#    #+#             */
/*   Updated: 2024/10/25 11:24:25 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_isascii(int argument1)
{
	if (argument1 >= 0 && argument1 <= 127)
		return (1);
	return (0);
}
/*
int main (void)
{
	int	a;

	a = 130;
	printf(" The result is : %d", ft_isascii(a));
}
*/