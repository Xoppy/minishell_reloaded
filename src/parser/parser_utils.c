/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:36:32 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/16 16:12:14 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int token_count(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
        i++;
    return (i);
}

t_tree  *new_node(const char *content)
{
    t_tree  *node;

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
	node->left = NULL;
    node->right = NULL;
    node->heredoc_fd = -1;
    node->start = -1;
    node->end = -1;
	printf("[LOOP %d][AST] new_node(%s) @ %p\n",g_loop_id, content, (void*)node);
	return (node);
}

t_tree	*make_command_node(char **tokens, int start, int end)
{
	int		total_len;
	int		i;
	char	*buf;
	t_tree	*node;

	total_len = 0;
	i = start;
	while (i <= end)
	{
		total_len += ft_strlen(tokens[i]) + 1;
		i++;
	}
	buf = malloc(total_len);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	i = start;
	while (i <= end)
	{
		ft_strlcat(buf, tokens[i], total_len);
		if (i < end)
			ft_strlcat(buf, " ", total_len);
		i++;
	}
	node = new_node(buf);
	free(buf);
	return (node);
}

int is_pipe(char *s)
{
    return (s && s[0] == '|' && !s[1]);
}

int is_redirect(char *s)
{
    return (s && (
        !ft_strcmp(s, "<") || !ft_strcmp(s, ">") ||
        !ft_strcmp(s, "<<") || !ft_strcmp(s, ">>")
    ));
}