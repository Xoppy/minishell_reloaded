/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:20:47 by ituriel           #+#    #+#             */
/*   Updated: 2025/07/28 14:27:49 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	skip_special(const char **sp)
{
	const char	*p;
	size_t		len;

	p = *sp;
	if ((*p == '<' || *p == '>') && p[1] == *p)
		p += 2;
	else
		p++;
	len = p - *sp;
	*sp = p;
	return (len);
}

static size_t	skip_word(const char **sp)
{
	const char	*p;
	int			in_sq;
	int			in_dq;
	size_t		len;

	p = *sp;
	in_sq = 0;
	in_dq = 0;
	while (*p && (!ft_isspace(*p) || in_sq || in_dq))
	{
		if (!in_sq && *p == '"')
			in_dq = !in_dq;
		else if (!in_dq && *p == '\'')
			in_sq = !in_sq;
		else if (!in_sq && !in_dq && is_special(*p))
			break ;
		p++;
	}
	len = p - *sp;
	*sp = p;
	return (len);
}

static size_t	get_token_len(const char **sp)
{
	if (is_special(**sp))
		return (skip_special(sp));
	return (skip_word(sp));
}

char	*next_token(const char **sp)
{
	const char	*start;
	size_t		toklen;
	char		*buf;

	while (**sp && ft_isspace(**sp))
		(*sp)++;
	start = *sp;
	toklen = get_token_len(sp);
	buf = malloc(toklen + 1);
	if (!buf)
		return (NULL);
	ft_strlcpy(buf, start, toklen + 1);
	return (buf);
}
