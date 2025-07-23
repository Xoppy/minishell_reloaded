/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:06:43 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/23 12:20:18 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_exec *context)
{
	t_envi	*node;
	size_t	i;

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
