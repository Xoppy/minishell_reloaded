/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/16 11:38:31 by cauffret          #+#    #+#             */
/*   Updated: 2024/10/25 11:24:22 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

int	ft_isalpha(int argument1)
{
	char	convert;

	convert = (char)argument1;
	if ((convert < 'A' || argument1 > 'Z') && (argument1 < 'a'
			|| argument1 > 'z'))
		return (0);
	return (1);
}
/*
int	main(void)
{
	int	a;

	a = 3;
	a = ft_isalpha('a');
	printf("%d", a);
}
*/