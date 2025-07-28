/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:05:06 by cauffret          #+#    #+#             */
/*   Updated: 2025/07/28 07:16:31 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_out_helper(int file_fd, int saved_stdout)
{
	close(file_fd);
	print_err_prefix("redirect");
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
	{
		print_err_prefix("critical error restoring stdout");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	close(saved_stdout);
	return (1);
}

int	redirect_out(t_tree *node, t_memory **shell, int flags)
{
	int	saved_stdout;
	int	file_fd;
	int	status;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
	{
		print_err_prefix("redirect");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	file_fd = open(node->right->argv[0], flags, 0644);
	if (file_fd < 0)
	{
		print_err_prefix(node->right->argv[0]);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close(saved_stdout);
		return (1);
	}
	if (dup2(file_fd, STDOUT_FILENO) < 0)
		return (redirect_out_helper(file_fd, saved_stdout));
	close(file_fd);
	status = executor_execute_ast(node->left, shell);
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
	{
		print_err_prefix("critical error restoring stdout");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	close(saved_stdout);
	return (status);
}

int	redirect_in(t_tree *node, t_memory **shell)
{
	int	saved_stdin;
	int	read_fd;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (1);
	read_fd = open(node->right->argv[0], O_RDONLY);
	if (read_fd < 0)
	{
		print_err_prefix(node->right->argv[0]);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close(saved_stdin);
		return (1);
	}
	if (dup2(read_fd, STDIN_FILENO) < 0)
	{
		close(read_fd);
		print_err_prefix("redirect");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		return (1);
	}
	close(read_fd);
	status = executor_execute_ast(node->left, shell);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (status);
}
