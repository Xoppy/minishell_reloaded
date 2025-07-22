    /* ************************************************************************** */
    /*                                                                            */
    /*                                                        :::      ::::::::   */
    /*   main.c                                             :+:      :+:    :+:   */
    /*                                                    +:+ +:+         +:+     */
    /*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
    /*                                                +#+#+#+#+#+   +#+           */
    /*   Created: 2025/07/08 14:05:57 by adi-marc          #+#    #+#             */
    /*   Updated: 2025/07/17 18:36:34 by ituriel          ###   ########.fr       */
    /*                                                                            */
    /* ************************************************************************** */

    #include "../includes/minishell.h"

    int   g_loop_id = 0;

    int main(int argc, char **argv, char **envp)
    {
        t_memory *shell;
        int status;

        (void)argc;
        (void)argv;
        signal_init();
        status = 0;
        shell_envi_init(&shell, envp);
        while (1)
        {
            g_loop_id++;
            printf("\n[LOOP %d] start\n", g_loop_id);
            shell->line = prompt_read_line("minishell$ ");
            if(!shell->line)
                break ;
            shell->tokens = lexer_split_tokens(shell->line);
            if (shell->tokens)
            {
                expand_tokens(&shell);
                shell->tree = parser_build_ast(&shell);
                ft_free_string_array(shell->tokens);
                shell->tokens = NULL;
                if (shell->tree)
                {
                    shell->status = executor_execute_ast(shell->tree, &shell);
                    parser_free_ast(shell->tree);
                    shell->tree = NULL;
                }
            }
            free(shell->line);
            shell->line = NULL;
        }
        status = shell->status;
        ft_free_shell(&shell);
        rl_clear_history();
        return (status);
    }
