/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:56:24 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 14:14:27 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_str(char *key, t_envi *env_list)
{
	t_envi	*current;

	current = env_list;
	while (current)
	{
		if (!ft_strcmp(current->env->key, key) && current->env->values
			&& current->env->values[0])
			return (ft_strdup(current->env->values[0]));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*append_str(char *origin, char *to_add)
{
	char	*joined;

	if (!origin)
		return (to_add);
	joined = ft_strjoin(origin, to_add);
	free(origin);
	free(to_add);
	return (joined);
}

void	expand_tokens(t_memory **shell)
{
	int		index;
	char	*expanded;
	char	**tokens;
	t_envi	*env_list;
	int		last_status;

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
