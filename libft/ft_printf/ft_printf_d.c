/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:04:29 by ituriel           #+#    #+#             */
/*   Updated: 2024/11/07 11:14:24 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf_d(va_list args)
{
	int	d;

	d = 0;
	d = va_arg(args, int);
	ft_putnbr_fd(d, 1);
	return (ft_count_digits(d));
}
