/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:24:00 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/22 11:47:07 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tree   *parse_range(char **tokens, int start, int end);
static int  find_token(char **tokens, int start, int end,
                        int (*checker)(char *));

t_tree  *parser_build_ast(t_memory **shell)
{
    int count;
    char **tokens;

    tokens = (*shell)->tokens;

    count = 0;
    while (tokens[count])
        count++;
    if (count == 0)
        return (NULL);
    return (parse_range(tokens, 0, count - 1));
}

static t_tree   *parse_range(char **tokens, int start, int end)
{
    int i;
    t_tree  *node;

    if (start > end)
        return (NULL);
    i = find_token(tokens, start, end, is_pipe);
    while (i >= 0)
    {
        node = new_node(tokens[i]);
         if (!node)
            return(NULL);
        node->left = parse_range(tokens, start, i - 1);
        node->right = parse_range(tokens, i + 1, end);
        if ((start < i && !node->left) || (i + 1 <= end && !node->right))
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
        if (!node)
            return (NULL);
        node->left = parse_range(tokens, start, i - 1);
        node->right = parse_range(tokens, i + 1, end);
        if ((start < i && !node->left) || (i + 1 <= end && !node->right))
        {
            parser_free_ast(node);
            return (NULL);
        }
        return (node);
    }
    return (make_command_node(tokens, start, end));
}

static int  find_token(char **tokens, int start, int end,
                        int (*checker)(char *))
{
    int i;

    i = end;
    while (i >= start)
    {
        if (checker(tokens[i]))
            return (i);
        i--;
    }
    return (-1);
}

void    parser_free_ast(t_tree *node)
{
    if (!node)
        return;
    parser_free_ast(node->left);
    parser_free_ast(node->right);
    if (node->content)
    {
        free(node->content);
        node->content = NULL;
    }
    free(node);
    node = NULL;
}
