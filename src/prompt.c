/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:52:36 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 06:46:42 by xoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Checks if the string contains unclosed quotes
static int	has_unclosed_quotes(const char *s)
{
	int	in_squote;
	int	in_dquote;

	in_squote = 0;
	in_dquote = 0;
	while (*s)
	{
		if (*s == 39 && !in_dquote)
			in_squote = !in_squote;
		else if (*s == 34 && !in_squote)
			in_dquote = !in_dquote;
		s++;
	}
	return (in_squote || in_dquote);
}

// Prompt the user with > if unclosed quotes
static char	*prompt_continue(char *prev)
{
	char	*cont;
	char	*joined;

	cont = readline("> ");
	if (!cont)
		return (prev);
	joined = ft_triple_strjoin(prev, "\n", cont);
	free(prev);
	free(cont);
	return (joined);
}

// Wait for user prompt and trim it if needed
char	*prompt_read_line(const char *prompt)
{
	char	*raw;
	char	*trimmed;

	raw = readline(prompt);
	if (!raw)
		return (NULL);
	while (has_unclosed_quotes(raw))
		raw = prompt_continue(raw);
	trimmed = ft_strtrim(raw, " \t\n");
	free(raw);
	if (*trimmed)
		add_history(trimmed);
	return (trimmed);
}
