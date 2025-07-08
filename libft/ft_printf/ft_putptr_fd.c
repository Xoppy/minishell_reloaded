/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:19:01 by ituriel           #+#    #+#             */
/*   Updated: 2024/11/07 11:14:47 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putptr_fd(uintptr_t ptr, int fd)
{
	int	count;

	count = 0;
	if (ptr >= 16)
	{
		count += ft_putptr_fd(ptr / 16, fd);
	}
	ft_putchar_fd("0123456789abcdef"[ptr % 16], fd);
	count++;
	return (count);
}
