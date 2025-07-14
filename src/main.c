/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:05:57 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/14 16:16:03 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_envi  *env_list;
    char    *line;
    char    **tokens;
    t_tree  *ast;
    int status;

    (void)argc;
    (void)argv;
    signal_init();
    env_init(&env_list, envp);
    status = 0;
    while (1)
    {
        line = prompt_read_line("minishell$ ");
        if(!line)
            break ;
        tokens = lexer_split_tokens(line);
        if (tokens)
        {
            expand_tokens(tokens, env_list, status);
            ast = parser_build_ast(tokens);
            ft_free_string_array(tokens);
            if (ast)
            {
                status = executor_execute_ast(ast, &env_list);
                parser_free_ast(ast);
            }
            tokens = NULL;
        }
        free(line);
        if (env_list->should_exit == 1)
            break;
    }
    if (tokens)
        ft_free_string_array(tokens);
    env_destroy(env_list);
    rl_clear_history();
    return (status);
}
