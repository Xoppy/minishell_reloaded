/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:48:26 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/27 23:39:12 by ituriel          ###   ########.fr       */
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

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		signal_init();
		return (perror("fork"), 1);
	}
	if (pid == 0)
	{
        signal(SIGINT,  SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
		child_process(argv, shell);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
+        write(STDERR_FILENO, "\n", 1);
	signal_init();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	check_cmd(char *cmd, t_memory **shell)
{
	char	*path;

	if (executor_is_builtin(cmd))
		return (0);
	if (!cmd)
	{
		write(2, "\n", 1);
		return(1);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (1);
	}
	path = find_in_path(cmd, (*shell)->envi);
	if (path)
	{
		free(path);
		return (0);
	}
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (1);
}

static int	exec_simple_cmd(t_tree *node, t_memory **shell)
{
	char	**argv;
	int		err;

	argv = node->argv;
	if (!argv || !argv[0])
		return ((*shell)->status);
	err = check_cmd(argv[0], shell);
	if (err)
	{
		return (127);
	}
	if (executor_is_builtin(argv[0]))
		(*shell)->status = exec_builtin_cmd(argv, shell);
	else
	{
		(*shell)->status = exec_external_cmd(argv, shell);
	}
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
