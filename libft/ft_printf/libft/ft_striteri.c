/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/25 18:07:58 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 18:07:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	uptoone(unsigned int i, char* c)
{
	*c += 1;
}
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != 0)
	{
		f(i, &s[i]);
		i++;
	}
}
/*
int main (void)
{
	char	hello[] = "abcde";

	ft_striteri(hello, uptoone);
	printf("The result is : %s", hello);
}
*/