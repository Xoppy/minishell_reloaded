/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:30:44 by ituriel           #+#    #+#             */
/*   Updated: 2024/11/07 11:14:24 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf_p(va_list args)
{
	int			d;
	uintptr_t	p;

	d = 0;
	p = (va_arg(args, uintptr_t));
	if (p == 0)
	{
		d += 5;
		ft_putstr_fd("(nil)", 1);
		return (d);
	}
	d += write(1, "0x", 2);
	d += (ft_putptr_fd(p, 1));
	return (d);
}
