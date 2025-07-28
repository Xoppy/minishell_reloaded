/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:59:44 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 06:45:50 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_env_count(t_envi *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*make_env_entry(t_envi *node)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin_arr(node->env->values, ':');
	if (!tmp)
		return (NULL);
	entry = ft_triple_strjoin(node->env->key, "=", tmp);
	free(tmp);
	return (entry);
}

char	**env_list_to_array(t_envi *env)
{
	char	**arr;
	char	*entry;
	size_t	len;
	size_t	i;

	len = get_env_count(env);
	arr = malloc(sizeof *arr * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		entry = make_env_entry(env);
		if (!entry)
			break ;
		arr[i++] = entry;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_envi	*duplicate_env_list(t_envi *env)
{
	t_envi	*copy;
	t_envi	*curr;

	copy = NULL;
	while (env)
	{
		curr = malloc(sizeof *curr);
		if (!curr)
			return (NULL);
		curr->env = malloc(sizeof *curr->env);
		if (!curr->env)
			return (NULL);
		curr->env->key = ft_strdup(env->env->key);
		curr->env->values = ft_strdup_arr(env->env->values);
		curr->prev = NULL;
		curr->next = copy;
		if (copy)
			copy->prev = curr;
		copy = curr;
		env = env->next;
	}
	return (copy);
}
