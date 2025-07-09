/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:56:24 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/09 13:21:05 by adi-marc         ###   ########.fr       */
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

static char	*append_str(char *original, const char *addition)
{
	char	*new_string;

	new_string = ft_strjoin(original, addition);
	free(original);
	return (new_string);
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
	int			in_single_quote;
	int			in_double_quote;

	result = ft_strdup("");
	cursor = token;
	in_single_quote = 0;
	in_double_quote = 0;
	while (*cursor)
	{
		if (*cursor == '\'' && in_double_quote == 0)
		{
			in_single_quote = !in_single_quote;
			cursor++;
		}
		else if (*cursor == '"' && in_single_quote == 0)
		{
			in_double_quote = !in_double_quote;
			cursor++;
		}
		else if (*cursor == '$' && in_single_quote == 0 && cursor[1] != '\0')
		{
			fragment = handle_dollar(&cursor, env_list, last_status);
			result = append_str(result, fragment);
			free(fragment);
		}
		else
		{
			char	temp_str[2];

			temp_str[0] = *cursor;
			temp_str[1] = '\0';
			result = append_str(result, temp_str);
			cursor++;
		}
	}
	return (result);
}

void	expand_tokens(char **tokens, t_envi *env_list, int last_status)
{
	int		index;
	char	*expanded;

	index = 0;
	while (tokens[index])
	{
		expanded = expand_token(tokens[index], env_list, last_status);
		free(tokens[index]);
		tokens[index] = expanded;
		index++;
	}
}