/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:05:06 by cauffret          #+#    #+#             */
/*   Updated: 2025/07/28 13:47:26 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	save_stdin(void)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd < 0)
	{
		print_err_prefix("redirect");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	return (fd);
}

static int	open_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_err_prefix(filename);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	return (fd);
}

static int	apply_redirect_in(int read_fd, int saved_fd)
{
	if (dup2(read_fd, STDIN_FILENO) < 0)
	{
		print_err_prefix("redirect");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close(read_fd);
		dup2(saved_fd, STDIN_FILENO);
		close(saved_fd);
		return (-1);
	}
	close(read_fd);
	return (0);
}

static void	restore_stdin(int saved_fd)
{
	if (dup2(saved_fd, STDIN_FILENO) < 0)
	{
		print_err_prefix("critical error restoring stdin");
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	close(saved_fd);
}

int	redirect_in(t_tree *node, t_memory **shell)
{
	int	saved_fd;
	int	read_fd;
	int	status;

	(void)shell;
	saved_fd = save_stdin();
	if (saved_fd < 0)
		return (1);
	read_fd = open_input(node->right->argv[0]);
	if (read_fd < 0)
	{
		close(saved_fd);
		return (1);
	}
	if (apply_redirect_in(read_fd, saved_fd) < 0)
		return (1);
	status = executor_execute_ast(node->left, shell);
	restore_stdin(saved_fd);
	return (status);
}
