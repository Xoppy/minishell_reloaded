/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:55:30 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 19:00:07 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *ft_triple_strjoin(const char *s1, const char *s2, const char *s3)
{
    char    *res;
    size_t  len_one;
    size_t  len_two;
    size_t  len_three;
    size_t  i;

    len_one = ft_strlen(s1);
    len_two = ft_strlen(s2);
    len_three = ft_strlen(s3);
    res = malloc(sizeof(char) * (len_one + len_two + len_three) + 1);
    if (!res)
        return (NULL);
    i = 0;
    while (*s1)
        res[i++] = *s1++;
    while (*s2)
        res[i++] = *s2++;
    while (*s3)
        res[i++] = *s3++;
    res[i] = '\0';
    return (res);
}

char    *ft_mini_strndup(const char *src, size_t n)
{
    char    *dup;
    size_t  i;

    dup = malloc(sizeof(char) * n + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n && src[i])
    {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

int ft_isspace(int c)
{
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}