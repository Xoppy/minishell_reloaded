/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strj_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:52:01 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 06:44:22 by xoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_arr_count(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static size_t	ft_arr_strlen(char **arr)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (arr[i])
	{
		len += ft_strlen(arr[i]);
		i++;
	}
	return (len);
}

static void	ft_arr_fill(char **arr, char sep, char *dst)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		ft_strlcpy(dst, arr[i], ft_strlen(arr[i]) + 1);
		dst += ft_strlen(arr[i]);
		if (arr[i + 1])
			*dst++ = sep;
		i++;
	}
	*dst = '\0';
}

char	*ft_strjoin_arr(char **arr, char sep)
{
	size_t	count;
	size_t	total;
	char	*res;

	count = ft_arr_count(arr);
	total = ft_arr_strlen(arr);
	if (count > 1)
		total += count - 1;
	res = malloc(total + 1);
	if (!res)
		return (NULL);
	ft_arr_fill(arr, sep, res);
	return (res);
}
