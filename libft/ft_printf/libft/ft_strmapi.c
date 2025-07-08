/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/25 17:37:43 by marvin            #+#    #+#             */
/*   Updated: 2024/10/25 17:37:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char byone (unsigned int i, char c)
{
	return (c+1);
}
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*final;
	unsigned int	i;
	int				length;

	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	i = 0;
	final = (char *)malloc(sizeof(char) * (length + 1));
	if (!final)
		return (NULL);
	while (s[i] != 0)
	{
		final[i] = (*f)(i, s[i]);
		i++;
	}
	final[i] = '\0';
	return (final);
}
/*
int main (void)
{
	char	*test;
	char	*test1;

	test = "abcde";
	test1 = ft_strmapi(test,byone);
	if (test1)
	{
		printf("All went up by one : %s\n", test1);
	}
	free(test1);
	return (0);
}
*/