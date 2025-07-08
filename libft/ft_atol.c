/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:46:51 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 18:46:53 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static void	ft_right_place(int *i, const char *nptr, int *sign)
{
	while (ft_isspace(nptr[*i]))
		(*i)++;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	current;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	ft_right_place(&i, nptr, &sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		current = (long)(nptr[i] - '0');
		result = result * 10 + current;
		i++;
	}
	return (result * sign);
}
