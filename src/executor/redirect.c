/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:28:35 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/17 18:41:42 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_out(t_tree *node,t_memory **shell, int flags);
static int	redirect_in(t_tree *node, t_memory **shell);
static int	redirect_heredoc(t_tree *node, t_memory **shell);

int exec_redirect_node(t_tree *node, t_memory **shell)
{
    if (!node || !node->content)
        return (1);
    if (ft_strcmp(node->content, ">") == 0)
        return (redirect_out(node, shell,
                            O_WRONLY | O_CREAT | O_TRUNC));
    if (ft_strcmp(node->content, ">>") == 0)
        return (redirect_out(node, shell,
                            O_WRONLY | O_CREAT | O_APPEND));
    if (ft_strcmp(node->content, "<") == 0)
            return (redirect_in(node, shell));
    if (ft_strcmp(node->content, "<<") == 0)
            return (redirect_heredoc(node, shell));
    return (1);
}

static void	restore_fd(int saved_fd, int target_fd)
{
	dup2(saved_fd, target_fd);
	close(saved_fd);
}

static int	redirect_out(t_tree *node,t_memory **shell, int flags)
{
	int	saved_stdout;
	int	file_fd;
	int	status;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		return (1);
	file_fd = open(node->right->content, flags, 0644);
	if (file_fd < 0)
	{
		ft_printf("minishell: %s: %s\n",
			node->right->content, strerror(errno));
		close(saved_stdout);
		return (1);
	}
	if (dup2(file_fd, STDOUT_FILENO) < 0)
	{
		close(file_fd);
		ft_printf("minishell: %s\n", strerror(errno));
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return (1);
	}
	close(file_fd);
	status = executor_execute_ast(node->left, shell);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (status);
}

static int	redirect_in(t_tree *node, t_memory **shell)
{
	int	saved_stdin;
	int	read_fd;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (1);
	read_fd = open(node->right->content, O_RDONLY);
	if (read_fd < 0)
	{
		ft_printf("minishell: %s: %s\n",
			node->right->content, strerror(errno));
		close(saved_stdin);
		return (1);
	}
	if (dup2(read_fd, STDIN_FILENO) < 0)
	{
		close(read_fd);
		ft_printf("minishell: %s\n", strerror(errno));
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

static int	redirect_heredoc(t_tree *node, t_memory **shell)
{
	int	saved_stdin;
	int	heredoc_fd;
	int	status;
	t_envi **env_list;

	env_list = &(*shell)->envi;
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (1);
	heredoc_fd = get_heredoc_fd(node->right->content, *env_list);
	if (heredoc_fd < 0)
	{
		restore_fd(saved_stdin, STDIN_FILENO);
		return (1);
	}
	if (dup2(heredoc_fd, STDIN_FILENO) < 0)
	{
		close(heredoc_fd);
		restore_fd(saved_stdin, STDIN_FILENO);
		return (1);
	}
	close(heredoc_fd);
	status = executor_execute_ast(node->left, shell);
	restore_fd(saved_stdin, STDIN_FILENO);
	return (status);
}
