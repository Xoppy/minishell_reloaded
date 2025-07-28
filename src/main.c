/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:05:57 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 14:35:21 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_line(t_memory *shell, char *line)
{
	char	**tokens;

	shell->line = line;
	tokens = lexer_split_tokens(line);
	shell->tokens = tokens;
	if (!tokens)
		return ;
	expand_tokens(&shell);
	shell->tree = parser_build_ast(&shell);
	ft_free_string_array(tokens);
	shell->tokens = NULL;
	if (shell->tree)
	{
		shell->status = executor_execute_ast(shell->tree, &shell);
		parser_free_ast(shell->tree);
		shell->tree = NULL;
	}
}

static int	run_shell(t_memory *shell)
{
	char	*line;

	while (1)
	{
		line = prompt_read_line("minishell$ ");
		if (!line)
			break ;
		handle_line(shell, line);
		free(line);
	}
	return (shell->status);
}

int	main(int argc, char **argv, char **envp)
{
	t_memory	*shell;
	int			status;

	(void)argc;
	(void)argv;
	signal_init();
	shell_envi_init(&shell, envp);
	status = run_shell(shell);
	ft_free_shell(&shell);
	rl_clear_history();
	return (status);
}
