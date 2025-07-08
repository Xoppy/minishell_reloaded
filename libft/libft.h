/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:00:06 by azaemeki13        #+#    #+#             */
/*   Updated: 2025/07/08 18:47:02 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

// GNL STRUCT
typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}					t_list;

int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t elementCount, size_t elementSize);
int		ft_count_digits(long long int n);
int		ft_isalnum(int argument1);
int		ft_isalpha(int argument1);
int		ft_isascii(int argument1);
int		ft_isdigit(int argument1);
int		ft_isprint(int argument1);
char	*ft_itoa(int n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
void	*ft_memcpy(void *destination, const void *source, size_t num);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *ptr, int value, size_t num);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *str1, const char *str2, size_t num);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int argument1);
int		ft_toupper(int argument1);

// GNL
void				buffer_to_stash(t_list **head, int fd);
int					newline_found(t_list *head);
void				append_node(t_list **head, char *buffer);
char				*rl_creator(t_list *head);
size_t				length_to_nl(t_list *head);
void				stash_to_line(t_list *head, char *return_line);
void				refresh_list(t_list **list);
t_list				*head_pos(t_list *list);
void				cleanup_list(t_list **list, t_list *new_node, char *buffer);
char				*get_next_line(int fd);

// GNL UTILS

#endif