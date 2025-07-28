/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:03:49 by ituriel           #+#    #+#             */
/*   Updated: 2025/07/28 14:04:50 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_dollar_status(const char **cursor, int last_status)
{
	char	*status_str;
	char	*expansion;

	status_str = ft_itoa(last_status);
	if (!status_str)
		return (NULL);
	expansion = ft_strdup(status_str);
	free(status_str);
	*cursor += 2;
	return (expansion);
}

static char	*handle_dollar_var(const char **cursor, t_envi *env_list)
{
	const char	*start;
	char		*key_str;
	char		*expansion;

	*cursor += 1;
	start = *cursor;
	while (ft_isalnum(**cursor) || **cursor == '_')
		(*cursor)++;
	key_str = ft_mini_strndup(start, *cursor - start);
	if (!key_str)
		return (NULL);
	expansion = get_env_str(key_str, env_list);
	free(key_str);
	return (expansion);
}

char	*handle_dollar(const char **cursor,
					t_envi *env_list,
					int last_status)
{
	if ((*cursor)[1] == '?')
		return (handle_dollar_status(cursor, last_status));
	if (ft_isalpha((*cursor)[1]) || (*cursor)[1] == '_')
		return (handle_dollar_var(cursor, env_list));
	*cursor += 1;
	return (ft_strdup("$"));
}
