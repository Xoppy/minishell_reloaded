/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:36:16 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 06:57:49 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**alloc_values(char *value)
{
	char	**vals;

	vals = malloc(sizeof(*vals) * 2);
	if (!vals)
		return (NULL);
	vals[0] = ft_strdup(value);
	if (!vals[0])
	{
		free(vals);
		return (NULL);
	}
	vals[1] = NULL;
	return (vals);
}

static t_envp	*create_entry(char *key, char **vals)
{
	t_envp	*entry;

	entry = malloc(sizeof(*entry));
	if (!entry)
		return (NULL);
	entry->key = ft_strdup(key);
	if (!entry->key)
	{
		free(entry);
		return (NULL);
	}
	entry->values = vals;
	return (entry);
}

static t_envi	*create_node(t_envi **env_list, t_envp *entry)
{
	t_envi	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->env = entry;
	node->prev = NULL;
	node->next = *env_list;
	if (*env_list)
		(*env_list)->prev = node;
	*env_list = node;
	return (node);
}

int	cd_add_env(t_envi **env_list, char *key, char *value)
{
	char	**vals;
	t_envp	*entry;
	t_envi	*node;

	vals = alloc_values(value);
	if (!vals)
		return (1);
	entry = create_entry(key, vals);
	if (!entry)
	{
		ft_free_string_array(vals);
		return (1);
	}
	node = create_node(env_list, entry);
	if (!node)
	{
		free(entry->key);
		ft_free_string_array(vals);
		free(entry);
		return (1);
	}
	return (0);
}

int	error_cd(char *target)
{
	if (!target)
	{
		print_err_prefix("cd");
		ft_putendl_fd("HOME not set", STDERR_FILENO);
		return (1);
	}
	else if (target == (char *)-1)
	{
		print_err_prefix("cd");
		ft_putendl_fd("OLDPWD not set", STDERR_FILENO);
		return (1);
	}
	return (0);
}
