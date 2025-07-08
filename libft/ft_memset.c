/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/02 10:00:13 by azaemeki13        #+#    #+#             */
/*   Updated: 2024/10/25 11:24:52 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

void	*ft_memset(void *ptr, int value, size_t num)
{
	char	*base;
	size_t	i;

	i = 0;
	base = (char *)ptr;
	while (i < num)
	{
		base[i] = (char)value;
		i++;
	}
	return (ptr);
}
/*
int main ()
{
  char str[] = "almost every programmer should know memset!";

  ft_memset (str,'-',6);
  puts (str);
  return (0);
}
*/
