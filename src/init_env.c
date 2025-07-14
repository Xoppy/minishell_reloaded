/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:38:04 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/14 13:08:36 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create a t_envp from a string "KEY=VALUE:VAL2:VAL3"
static t_envp   *envp_create(char *entry)
{
    t_envp  *node;
    char    *sep;

    sep = ft_strchr(entry, '=');
    if (!sep)
        return (NULL);
    node = malloc(sizeof(*node));
    if (!node)
        return(NULL);
    node->key = ft_mini_strndup(entry, sep - entry);
    if (!node->key)
    {
        free(node);
        return (NULL);
    }
    node->values = ft_split(sep + 1, ':');
    if (!node->values)
    {
        free(node->key);
        free(node);
        return (NULL);
    }
    return (node);
}

// Initialize the env list
void    env_init(t_envi **shell, char **envp)
{
    t_envi  *head;
    t_envi  *current;
    t_envp  *entry;
    int i;

    head = NULL;
    i = 0;
    while (envp[i])
    {
        entry = envp_create(envp[i]);
        if (entry)
        {
            current = malloc(sizeof(*current));
            if(!current)
                break ;
            current->env = entry;
            current->should_exit = 0;
            current->prev = NULL;
            current->next = head;
            if (head)
                head->prev = current;
            head = current;
        }
        i++;
    }
    *shell = head;
}

// Destroy the entire env list
void    env_destroy(t_envi *shell)
{
    t_envi  *tmp;

    while(shell)
    {
        tmp = shell->next;
        free(shell->env->key);
        ft_free_string_array(shell->env->values);
        free(shell->env);
        free(shell);
        shell = tmp;
    }
}
