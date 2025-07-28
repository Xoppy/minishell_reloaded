/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:35:48 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 07:18:04 by xoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_entry(t_envi **env_list, char *name)
{
	t_envi	*curr;

	curr = *env_list;
	while (curr)
	{
		if (ft_strcmp(curr->env->key, name) == 0)
		{
			if (curr->prev)
				curr->prev->next = curr->next;
			else
				*env_list = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			free(curr->env->key);
			ft_free_string_array(curr->env->values);
			free(curr->env);
			free(curr);
			return ;
		}
		curr = curr->next;
	}
}

int	builtin_unset(t_exec *context)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (context->argv[i])
	{
		if (context->argv[i][0] == '\0' || (!ft_isalpha(context->argv[i][0])
				&& context->argv[i][0] != '_'))
		{
			print_err_prefix("unset");
			ft_putstr_fd("`", STDERR_FILENO);
			ft_putstr_fd(context->argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
		}
		else
			remove_env_entry(&context->env, context->argv[i]);
		i++;
	}
	return (status);
}
