/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:10:18 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/16 14:57:01 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int  update_existing(t_envi **env_list, char *key, char **vals)
{
    t_envi *node;

    node = *env_list;
    while(node)
    {
        if (ft_strcmp(node->env->key, key) == 0)
        {
            ft_free_string_array(node->env->values);
            node->env->values = vals;
            free(key);
            return (1);
        }
        node = node->next;
    }
    return (0);
}

static int  prepend_node(t_envi **env_list, char *key, char **vals)
{
    t_envi *node;

    node = malloc(sizeof *node);
    if (!node)
        return (1);
    node->env = malloc(sizeof *node->env);
    if (!node->env)
    {
        free(node);
        return (1);
    }
    node->env->key = key;
    node->env->values = vals;
    node->should_exit = 0;
    node->prev = NULL;
    node->next = *env_list;
    if (*env_list)
        (*env_list)->prev = node;
    *env_list = node;
    return (0);
}

static int  prepare_key_vals(const char *arg, char **key, char ***vals)
{
    char	*delim;

	delim = ft_strchr(arg, '=');
	if (!delim)
		return (0);
	*key = ft_mini_strndup(arg, delim - arg);
	if (!*key)
		return (1);
	if (!is_valid_name(*key))
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", *key);
		free(*key);
		return (-1);
	}
	*vals = ft_split(delim + 1, ':');
	if (!*vals)
	{
		free(*key);
		return (1);
	}
	return (2);
}

int add_or_update(t_envi **env_list, const char *arg)
{
    char *key;
    char    **vals;
    int status;

    status = prepare_key_vals(arg, &key, &vals);
    if (status == 0)
        return (0);
    if (status == 1 || status == -1)
        return (1);
    if (update_existing(env_list, key, vals))
        return (0);
    if (prepend_node(env_list, key, vals))
    {
        free(key);
        ft_free_string_array(vals);
        return (1);
    }
    return (0);
}

int builtin_export(t_exec *context)
{
    int i;
    int err;

    if (!context->argv[1])
        return (0);
    i = 1;
    err = 0;
    while (context->argv[i])
    {
        if (add_or_update(&context->env, context->argv[i]))
            err = 1;
        i++;
    }
    return (err);
}