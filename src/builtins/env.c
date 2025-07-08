/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:06:43 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 18:45:23 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_env(t_exec *context)
{
    t_envi  *node;
    size_t  i;

    node = context->env;
    while (node)
    {
        if (node->env->key && node->env->values)
        {
            ft_printf("%s=", node->env->key);
            i = 0;
            while (node->env->values[i])
            {
                ft_printf("%s", node->env->values[i]);
                if (node->env->values[i + 1])
                    ft_printf(":");
                i++;
            }
            ft_printf("\n");
        }
        node = node->next;
    }
    return (0);
}