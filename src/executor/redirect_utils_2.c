/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:30:51 by ituriel           #+#    #+#             */
/*   Updated: 2025/07/28 13:44:20 by ituriel          ###   ########.fr       */
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

static int	setup_redirect_out(char *filename, int flags)
{
	int	saved_fd;
	int	file_fd;

	saved_fd = dup(STDOUT_FILENO);
	if (saved_fd < 0)
	{
		print_err_prefix("redirect");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (-1);
	}
	file_fd = open(filename, flags, 0644);
	if (file_fd < 0)
	{
		print_err_prefix(filename);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close(saved_fd);
		return (-1);
	}
	if (dup2(file_fd, STDOUT_FILENO) < 0)
	{
		redirect_out_helper(file_fd, saved_fd);
		return (-1);
	}
	close(file_fd);
	return (saved_fd);
}

static void	teardown_redirect_out(int saved_fd)
{
	if (dup2(saved_fd, STDOUT_FILENO) < 0)
	{
		print_err_prefix("critical error restoring stdout");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	close(saved_fd);
}

int	redirect_out(t_tree *node, t_memory **shell, int flags)
{
	int	saved_fd;
	int	status;

	saved_fd = setup_redirect_out(node->right->argv[0], flags);
	if (saved_fd < 0)
		return (1);
	status = executor_execute_ast(node->left, shell);
	teardown_redirect_out(saved_fd);
	return (status);
}
