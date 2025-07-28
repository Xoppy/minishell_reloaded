/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:24:00 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 07:19:22 by xoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tree	*parse_range(char **tokens, int start, int end);
static int		find_token(char **tokens, int start, int end,
					int (*checker)(char *));

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

static t_tree	*make_empty_command(void)
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

static t_tree	*parse_range(char **tokens, int start, int end)
{
	int		i;
	t_tree	*node;

	if (start > end)
		return (NULL);
	i = find_token(tokens, start, end, is_pipe);
	if (i >= 0)
	{
		node = new_node(tokens[i]);
		node->left = parse_range(tokens, start, i - 1);
		node->right = parse_range(tokens, i + 1, end);
		if (!node->left || !node->right)
		{
			parser_free_ast(node);
			return (NULL);
		}
		return (node);
	}
	i = find_token(tokens, start, end, is_redirect);
	if (i >= 0)
	{
		node = new_node(tokens[i]);
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
	return (make_command_node(tokens, start, end));
}

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
