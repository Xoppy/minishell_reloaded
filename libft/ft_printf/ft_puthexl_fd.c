/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:01:38 by ituriel           #+#    #+#             */
/*   Updated: 2024/11/07 12:10:36 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_puthexl_fd(unsigned int nbr, int fd)
{
	unsigned int	count;

	count = 0;
	if (nbr >= 16)
	{
		count += ft_puthexl_fd((nbr / 16), fd);
	}
	ft_putchar_fd("0123456789abcdef"[nbr % 16], fd);
	count++;
	return (count);
}
