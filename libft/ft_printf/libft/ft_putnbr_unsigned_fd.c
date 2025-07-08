/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:24:19 by ituriel           #+#    #+#             */
/*   Updated: 2024/11/07 12:25:35 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_unsigned_fd(unsigned int nb, int fd)
{
	if (nb > 9)
	{
		ft_putnbr_unsigned_fd((nb / 10), fd);
	}
	ft_putchar_fd((nb % 10 + '0'), fd);
}
