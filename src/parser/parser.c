/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:24:00 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/16 16:13:34 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tree   *parse_range(char **tokens, int start, int end);
static int  find_token(char **tokens, int start, int end,
                        int (*checker)(char *));

t_tree  *parser_build_ast(char **tokens)
{
    int count;

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
        node->left = parse_range(tokens, start, i - 1);
        node->right = parse_range(tokens, i + 1, end);
        return (node);
    }
    i = find_token(tokens, start, end, is_redirect);
    if (i >= 0)
    {
        node = new_node(tokens[i]);
        node->left = parse_range(tokens, start, i - 1);
        node->right = parse_range(tokens, i + 1, end);
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
printf("[LOOP %d][AST DEBUG] free start: node(%s) @ %p left=%p right=%p\n",
           g_loop_id,
           node->content,
           (void*)node,
           (void*)node->left,
           (void*)node->right);
    parser_free_ast(node->left);
    parser_free_ast(node->right);
    printf("[LOOP %d][AST DEBUG] free content: \"%s\" @ %p\n",
           g_loop_id, node->content, (void*)node->content);
    if (node->content)
        free(node->content);
    printf("[LOOP %d][AST DEBUG] free node @ %p\n",
           g_loop_id, (void*)node);
    free(node);
}