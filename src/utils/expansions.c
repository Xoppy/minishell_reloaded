/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:56:24 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/17 16:51:39 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_str(char *key, t_envi *env_list)
{
	t_envi	*current;

	current = env_list;
	while (current)
	{
		if (!ft_strcmp(current->env->key, key)
			&& current->env->values && current->env->values[0])
			return (ft_strdup(current->env->values[0]));
		current = current->next;
	}
	return (ft_strdup(""));
}

static char *append_str(char *origin, char *to_add)
{
	char *joined;

    if (!origin)
        return to_add;     // just return fragment, don’t strdup()
    joined = ft_strjoin(origin, to_add);
    free(origin);
    free(to_add);
    return joined;
}

static char	*handle_dollar(const char **cursor, t_envi *env_list,
							int last_status)
{
	const char	*start;
	char		*key_str;
	char		*expansion;
	char		*status_str;

	if ((*cursor)[1] == '?')
	{
		status_str = ft_itoa(last_status);
		expansion = ft_strdup(status_str);
		free(status_str);
		*cursor += 2;
		return (expansion);
	}
	if (ft_isalpha((*cursor)[1]) || (*cursor)[1] == '_')
	{
		*cursor += 1;
		start = *cursor;
		while (ft_isalnum(**cursor) || **cursor == '_')
			(*cursor)++;
		key_str = ft_mini_strndup(start, *cursor - start);
		expansion = get_env_str(key_str, env_list);
		free(key_str);
		return (expansion);
	}
	/* lone '$' */
	*cursor += 1;
	return (ft_strdup("$"));
}

char	*expand_token(const char *token, t_envi *env_list, int last_status)
{
	const char	*cursor;
	char		*result;
	char		*fragment;
	int			in_single;
	int			in_double;

	cursor    = token;
	result    = NULL;
	in_single = 0;
	in_double = 0;
	while (*cursor)
	{
		if (toggle_quotes(*cursor, &in_single, &in_double))
		{
			cursor++;
			continue;
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

void	expand_tokens(t_memory **shell)
{
	int		index;
	char	*expanded;
	char **tokens;
	t_envi *env_list;
	int last_status;

	tokens = (*shell)->tokens;
	env_list = (*shell)->envi;
	last_status = (*shell)->status;
	index = 0;
	while (tokens[index])
	{
		expanded = expand_token(tokens[index], env_list, last_status);
		free(tokens[index]);
		tokens[index] = expanded;
		index++;
	}
}
