/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:25:28 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 14:12:36 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	toggle_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !*in_double)
	{
		*in_single = !*in_single;
		return (1);
	}
	if (c == '"' && !*in_single)
	{
		*in_double = !*in_double;
		return (1);
	}
	return (0);
}

static void	factor_core(char **result, int *in_single, int *in_double)
{
	*result = NULL;
	*in_single = 0;
	*in_double = 0;
}

static char	*expand_core(const char *token, t_envi *env_list, int last_status)
{
	const char	*cursor;
	char		*result;
	char		*fragment;
	int			in_single;
	int			in_double;

	cursor = token;
	factor_core(&result, &in_single, &in_double);
	while (*cursor)
	{
		if (toggle_quotes(*cursor, &in_single, &in_double))
		{
			cursor++;
			continue ;
		}
		if (*cursor == '$' && !in_single && cursor[1] != '\0')
			fragment = handle_dollar(&cursor, env_list, last_status);
		else
		{
			fragment = ft_mini_strndup(cursor, 1);
			cursor++;
		}
		result = append_str(result, fragment);
	}
	return (result);
}

char	*expand_token(const char *token, t_envi *env_list, int last_status)
{
	char	*res;

	res = expand_core(token, env_list, last_status);
	if (!res)
		res = ft_mini_strndup("", 0);
	return (res);
}
