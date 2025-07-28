/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:24:00 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 13:56:14 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*parser_build_ast(t_memory **shell)
{
	int		count;
	char	**tokens;

	tokens = (*shell)->tokens;
	count = 0;
	while (tokens[count])
		count++;
	if (count == 0)
		return (NULL);
	return (parse_range(tokens, 0, count - 1));
}

t_tree	*make_empty_command(void)
{
	t_tree	*n;

	n = malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->content = NULL;
	n->argv = malloc(sizeof(char *));
	if (!n->argv)
	{
		free(n);
		return (NULL);
	}
	n->argv[0] = NULL;
	n->left = NULL;
	n->right = NULL;
	n->heredoc_fd = -1;
	n->start = -1;
	n->end = -1;
	return (n);
}

void	parser_free_ast(t_tree *node)
{
	if (!node)
		return ;
	parser_free_ast(node->left);
	parser_free_ast(node->right);
	if (node->content)
	{
		free(node->content);
		node->content = NULL;
	}
	if (node->argv)
	{
		ft_free_string_array(node->argv);
		node->argv = NULL;
	}
	free(node);
	node = NULL;
}
