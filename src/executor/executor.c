/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:48:26 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/23 12:59:49 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_builtin_cmd(char **argv, t_memory **shell)
{
	t_envi	**env_list;
	int		result;

	env_list = &(*shell)->envi;
	(*shell)->exec = malloc(sizeof(t_exec));
	if (!(*shell)->exec)
		return (1);
	(*shell)->exec->argv = argv;
	(*shell)->exec->env = *env_list;
	(*shell)->exec->status = 0;
	result = executor_run_builtin((*shell)->exec, shell);
	*env_list = (*shell)->exec->env;
	free((*shell)->exec);
	(*shell)->exec = NULL;
	return (result);
}

static int	exec_external_cmd(char **argv, t_memory **shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		child_process(argv, shell);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	exec_simple_cmd(t_tree *node, t_memory **shell)
{
	char	**argv;

	argv = ft_split(node->content, ' ');
	if (!argv)
		return (1);
	if (executor_is_builtin(argv[0]))
		(*shell)->status = exec_builtin_cmd(argv, shell);
	else
		(*shell)->status = exec_external_cmd(argv, shell);
	ft_free_string_array(argv);
	return ((*shell)->status);
}

int	executor_execute_ast(t_tree *node, t_memory **shell)
{
	if (!node)
		return (0);
	if (is_pipe(node->content))
		return (exec_pipe_node(shell, node));
	if (is_redirect(node->content))
		return (exec_redirect_node(node, shell));
	return (exec_simple_cmd(node, shell));
}
