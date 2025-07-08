/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexu_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:07:37 by ituriel           #+#    #+#             */
/*   Updated: 2024/11/07 12:12:06 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_puthexu_fd(unsigned int nbr, int fd)
{
	unsigned int	count;

	count = 0;
	if (nbr >= 16)
	{
		count += ft_puthexu_fd((nbr / 16), fd);
	}
	ft_putchar_fd("0123456789ABCDEF"[nbr % 16], 1);
	count++;
	return (count);
}
