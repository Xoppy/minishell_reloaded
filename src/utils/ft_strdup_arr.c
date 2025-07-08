/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:54:58 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 18:55:15 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_dup(char **dup, size_t filled)
{
	while (filled--)
		free(dup[filled]);
	free(dup);
}

static int	ft_arr_dup_strs(char **arr, char **dup, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
		{
			ft_free_dup(dup, i);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_strdup_arr(char **arr)
{
	size_t	count;
	char	**dup;

	count = ft_arr_count(arr);
	dup = malloc((count + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	if (!ft_arr_dup_strs(arr, dup, count))
		return (NULL);
	dup[count] = NULL;
	return (dup);
}