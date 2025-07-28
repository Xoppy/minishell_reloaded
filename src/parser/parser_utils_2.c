/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:51:16 by ituriel           #+#    #+#             */
/*   Updated: 2025/07/28 13:56:15 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_token(char **tokens, int start, int end,
		int (*checker)(char *))
{
	int	i;

	i = end;
	while (i >= start)
	{
		if (checker(tokens[i]))
			return (i);
		i--;
	}
	return (-1);
}

static t_tree	*handle_pipe(char **tokens, int start, int end)
{
	int		i;
	t_tree	*node;

	i = find_token(tokens, start, end, is_pipe);
	if (i < 0)
		return (NULL);
	node = new_node(tokens[i]);
	if (!node)
		return (NULL);
	node->left = parse_range(tokens, start, i - 1);
	node->right = parse_range(tokens, i + 1, end);
	if (!node->left || !node->right)
	{
		parser_free_ast(node);
		return (NULL);
	}
	return (node);
}

static t_tree	*handle_redirect(char **tokens, int start, int end)
{
	int		i;
	t_tree	*node;

	i = find_token(tokens, start, end, is_redirect);
	if (i < 0)
		return (NULL);
	node = new_node(tokens[i]);
	if (!node)
		return (NULL);
	node->right = parse_range(tokens, i + 1, end);
	if (!node->right)
	{
		parser_free_ast(node);
		return (NULL);
	}
	if (i > start)
		node->left = parse_range(tokens, start, i - 1);
	else
		node->left = make_empty_command();
	return (node);
}

t_tree	*parse_range(char **tokens, int start, int end)
{
	t_tree	*node;

	if (start > end)
		return (NULL);
	node = handle_pipe(tokens, start, end);
	if (node)
		return (node);
	node = handle_redirect(tokens, start, end);
	if (node)
		return (node);
	return (make_command_node(tokens, start, end));
}

int	token_count(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}
