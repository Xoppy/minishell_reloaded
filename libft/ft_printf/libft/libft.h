/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:00:06 by azaemeki13        #+#    #+#             */
/*   Updated: 2024/11/07 12:25:31 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t elementCount, size_t elementSize);
int				ft_count_digits(long long int n);
unsigned int	ft_count_digitsu(unsigned int n);
int				ft_isalnum(int argument1);
int				ft_isalpha(int argument1);
int				ft_isascii(int argument1);
int				ft_isdigit(int argument1);
int				ft_isprint(int argument1);
char			*ft_itoa(int n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
void			*ft_memcpy(void *destination, const void *source, size_t num);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *ptr, int value, size_t num);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_puthexl_fd(unsigned int nbr, int fd);
int				ft_puthexu_fd(unsigned int nbr, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr_unsigned_fd(unsigned int nb, int fd);
int				ft_putptr_fd(uintptr_t ptr, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_printf(const char *format, ...);
int				ft_printf_char(va_list args);
int				ft_printf_d(va_list args);
int				ft_printf_p(va_list args);
int				ft_printf_parser(char format, va_list args);
int				ft_printf_s(va_list args);
int				ft_printf_x(va_list args);
int				ft_printf_xu(va_list args);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *src);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *str1, const char *str2, size_t num);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int argument1);
int				ft_toupper(int argument1);

#endif
