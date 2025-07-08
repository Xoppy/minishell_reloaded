/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/16 15:01:33 by cauffret          #+#    #+#             */
/*   Updated: 2024/10/25 11:38:04 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_tolower(int argument1)
{
	if (argument1 >= 'A' && argument1 <= 'Z')
		return (argument1 += 32);
	return (argument1);
}
/*
int	main(void)
{
	char	a;

	a = 'b';
	printf("To upper result from %c is : %c ", a, ft_toupper(a));
}
*/