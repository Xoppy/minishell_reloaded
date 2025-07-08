/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:39:42 by ituriel           #+#    #+#             */
/*   Updated: 2024/11/07 12:02:29 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf_parser(char format, va_list args)
{
	int	d;

	d = 0;
	if (format == 'd' || format == 'i')
		d += ft_printf_d(args);
	if (format == 'c')
		d += ft_printf_char(args);
	if (format == 'u')
		d += ft_printf_u(args);
	if (format == 'p')
		d += ft_printf_p(args);
	if (format == 's')
		d += ft_printf_s(args);
	if (format == 'x')
		d += ft_printf_x(args);
	if (format == 'X')
		d += ft_printf_xu(args);
	if (format == '%')
	{
		d++;
		ft_putchar_fd('%', 1);
	}
	return (d);
}
