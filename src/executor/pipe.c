/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:12:44 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 06:40:57 by xoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	is_left_utils(int *fd, t_tree *node, t_memory **shell)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(fd[1]);
	executor_execute_ast(node->left, shell);
}

static pid_t	fork_pipe_child(int *fd, t_tree *node, t_memory **shell,
		int is_left)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (is_left)
			is_left_utils(fd, node, shell);
		else
		{
			close(fd[1]);
			if (dup2(fd[0], STDIN_FILENO) < 0)
				exit(EXIT_FAILURE);
			close(fd[0]);
			executor_execute_ast(node->right, shell);
		}
		ft_free_shell(shell);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

static int	fork_error(int *fd)
{
	print_error("minishell: fork failed\n");
	close(fd[0]);
	close(fd[1]);
	return (1);
}

static int	parent_waits(pid_t pid_left, pid_t pid_right, int *fd)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	signal_init();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_pipe_node(t_memory **shell, t_tree *node)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(fd) < 0)
	{
		print_error("minishell: pipe failed\n");
		return (1);
	}
	pid_left = fork_pipe_child(fd, node, shell, 1);
	if (pid_left < 0)
		return (fork_error(fd));
	pid_right = fork_pipe_child(fd, node, shell, 0);
	if (pid_right < 0)
		return (fork_error(fd));
	return (parent_waits(pid_left, pid_right, fd));
}
