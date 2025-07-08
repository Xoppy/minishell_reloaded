/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:00:06 by azaemeki13        #+#    #+#             */
/*   Updated: 2024/11/07 12:14:34 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int				ft_puthexl_fd(unsigned int nbr, int fd);
int				ft_puthexu_fd(unsigned int nbr, int fd);
int				ft_putptr_fd(uintptr_t ptr, int fd);
int				ft_printf(const char *format, ...);
int				ft_printf_char(va_list args);
int				ft_printf_d(va_list args);
int				ft_printf_p(va_list args);
int				ft_printf_parser(char format, va_list args);
int				ft_printf_s(va_list args);
unsigned int	ft_printf_u(va_list args);
int				ft_printf_x(va_list args);
int				ft_printf_xu(va_list args);

#endif
