/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/16 12:28:48 by cauffret          #+#    #+#             */
/*   Updated: 2024/10/25 11:24:14 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_isalnum(int argument1)
{
	char	convert;

	convert = (char)argument1;
	if ((convert < 48 || convert > 57) && (convert < 65 || convert > 90)
		&& (convert < 97 || convert > 122))
		return (0);
	return (1);
}
/*
int main (void)
{
	printf("The result is %d:" , ft_isalphanumeric('|'));
}
*/
