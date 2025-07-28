/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:36:32 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 13:56:15 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*new_node(const char *content)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree) * 1);
	if (!node)
	{
		return (NULL);
	}
	node->content = ft_strdup(content);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	node->argv = NULL;
	node->left = NULL;
	node->right = NULL;
	node->heredoc_fd = -1;
	node->start = -1;
	node->end = -1;
	return (node);
}

char	**dup_argv(char **tokens, int start, int end)
{
	int		len;
	char	**argv;
	int		i;

	len = end - start + 1;
	argv = malloc(sizeof(*argv) * (len + 1));
	i = 0;
	while (i < len)
	{
		argv[i] = ft_strdup(tokens[start + i]);
		if (!argv[i])
		{
			while (i-- > 0)
				free(argv[i]);
			free(argv);
			return (NULL);
		}
		i++;
	}
	argv[len] = NULL;
	return (argv);
}

t_tree	*make_command_node(char **tokens, int start, int end)
{
	t_tree	*node;

	node = malloc(sizeof(*node));
	node->content = NULL;
	node->argv = dup_argv(tokens, start, end);
	if (!node->argv)
	{
		free(node);
		return (NULL);
	}
	node->left = NULL;
	node->right = NULL;
	node->heredoc_fd = -1;
	node->start = start;
	node->end = end;
	return (node);
}

int	is_pipe(char *s)
{
	return (s && s[0] == '|' && !s[1]);
}

int	is_redirect(char *s)
{
	return (s && (!ft_strcmp(s, "<") || !ft_strcmp(s, ">") || !ft_strcmp(s,
				"<<") || !ft_strcmp(s, ">>")));
}
