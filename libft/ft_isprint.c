/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/16 14:40:12 by cauffret          #+#    #+#             */
/*   Updated: 2024/10/25 11:24:32 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
int	ft_isprint(int argument1)
{
	if ((argument1 >= 32 && argument1 <= 126))
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	a;

	a = 125;
	printf("The result is: %d", ft_isprintable(a));
	return (0);
}
*/