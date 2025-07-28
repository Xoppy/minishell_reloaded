/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:48:56 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 14:18:55 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// free an array of strings and the array itself
void	ft_free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

static void	clear_env_tree_exec(t_memory *sh)
{
	if (sh->envi)
	{
		env_destroy(sh->envi);
		sh->envi = NULL;
	}
	if (sh->tree)
	{
		parser_free_ast(sh->tree);
		sh->tree = NULL;
	}
	if (sh->exec)
	{
		sh->exec->env = NULL;
		sh->exec->ast = NULL;
		free(sh->exec);
		sh->exec = NULL;
	}
}

static void	clear_line_tokens(t_memory *sh)
{
	if (sh->line)
	{
		free(sh->line);
		sh->line = NULL;
	}
	if (sh->tokens)
	{
		ft_free_string_array(sh->tokens);
		sh->tokens = NULL;
	}
}

void	ft_free_shell(t_memory **shell)
{
	if (!shell || !*shell)
		return ;
	clear_env_tree_exec(*shell);
	clear_line_tokens(*shell);
	free(*shell);
	*shell = NULL;
}
