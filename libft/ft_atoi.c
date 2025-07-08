/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/23 12:03:23 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 11:24:04 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static void	ft_right_place(int *i, const char *nptr, int *f)
{
	while (ft_isspace(nptr[*i]))
		(*i)++;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			*f = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	f;
	int	current;
	int	final;

	final = 0;
	i = 0;
	f = 1;
	ft_right_place(&i, nptr, &f);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		current = nptr[i] - '0';
		final = final * 10 + current;
		i++;
	}
	return (final * f);
}
