/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:02:48 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 06:46:49 by xoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

// Count the number of tokens to be extract
static size_t	count_tokens(const char *s)
{
	size_t	count;
	int		in_sq;
	int		in_dq;

	count = 0;
	in_sq = 0;
	in_dq = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		count++;
		if (!in_sq && !in_dq && is_special(*s))
		{
			if ((*s == '<' || *s == '>') && s[1] == *s)
				s += 2;
			else
				s++;
		}
		else
		{
			while (*s && (!ft_isspace(*s) || in_sq || in_dq))
			{
				if (!in_sq && *s == 34)
					in_dq = !in_dq;
				else if (!in_dq && *s == 39)
					in_sq = !in_sq;
				else if (!in_sq && !in_dq && is_special(*s))
					break ;
				s++;
			}
		}
	}
	return (count);
}

// Extract the next token into a malloc buffer
static char	*next_token(const char **sp)
{
	const char	*start;
	const char	*s;
	char		*buf;
	size_t		len;
	int			in_sq;
	int			in_dq;

	len = 0;
	in_sq = 0;
	in_dq = 0;
	s = *sp;
	while (ft_isspace(*s))
		s++;
	start = s;
	if (!in_sq && !in_dq && is_special(*s))
	{
		if ((s[0] == '<' || s[0] == '>') && s[1] == s[0])
			len = 2;
		else
			len = 1;
	}
	else
	{
		while (*s && (!ft_isspace(*s) || in_sq || in_dq))
		{
			if (!in_sq && *s == 34)
				in_dq = !in_dq;
			else if (!in_dq && *s == 39)
				in_sq = !in_sq;
			else if (!in_sq && !in_dq && is_special(*s))
				break ;
			s++;
		}
		len = s - start;
	}
	buf = malloc(len + 1);
	if (!buf)
		return (NULL);
	ft_strlcpy(buf, start, len + 1);
	*sp = start + len;
	return (buf);
}

char	**lexer_split_tokens(const char *input_line)
{
	size_t		n;
	size_t		i;
	char		**tokens;
	const char	*p;

	n = count_tokens(input_line);
	i = 0;
	tokens = malloc(sizeof(*tokens) * (n + 1));
	p = input_line;
	if (!tokens)
		return (NULL);
	while (i < n)
		tokens[i++] = next_token(&p);
	tokens[i] = NULL;
	return (tokens);
}
