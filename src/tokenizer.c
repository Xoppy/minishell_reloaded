/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:02:48 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 14:28:46 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	skip_spaces(const char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
}

static void	skip_token(const char **s)
{
	int	in_sq;
	int	in_dq;

	in_sq = 0;
	in_dq = 0;
	if (is_special(**s))
	{
		if (((*s)[0] == '<' || (*s)[0] == '>') && (*s)[1] == (*s)[0])
			*s += 2;
		else
			(*s)++;
		return ;
	}
	while (**s && (in_sq || in_dq || !ft_isspace(**s)))
	{
		if (!in_sq && **s == '"')
			in_dq = !in_dq;
		else if (!in_dq && **s == '\'')
			in_sq = !in_sq;
		else if (!in_sq && !in_dq && is_special(**s))
			break ;
		(*s)++;
	}
}

static size_t	count_tokens(const char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		skip_spaces(&s);
		if (!*s)
			break ;
		count++;
		skip_token(&s);
	}
	return (count);
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
