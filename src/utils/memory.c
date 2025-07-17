/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:48:56 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/17 19:07:20 by ituriel          ###   ########.fr       */
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

void ft_free_shell(t_memory **shell)
{
    if ((*shell)->envi)
    {
        env_destroy((*shell)->envi);
        (*shell)->envi = NULL;
    }
    if ((*shell)->tree)
    {
        parser_free_ast((*shell)->tree);
        (*shell)->tree = NULL;
    }
    if ((*shell)->exec)
    {
        if ((*shell)->exec->argv)
            ft_free_string_array((*shell)->exec->argv);
        (*shell)->exec->env = NULL;
        (*shell)->exec->ast = NULL;
        free((*shell)->exec);
        (*shell)->exec = NULL;
    }
    if ((*shell)->line)
    {
        free((*shell)->line);
        (*shell)->line = NULL;
    }
    if ((*shell)->tokens)
    {
        ft_free_string_array((*shell)->tokens);
        (*shell)->tokens = NULL;
    }
    free(*shell);
    *shell = NULL;
}
