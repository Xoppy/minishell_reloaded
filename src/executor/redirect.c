/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:28:35 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/27 21:45:23 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_heredoc(t_tree *node, t_memory **shell);

int	exec_redirect_node(t_tree *node, t_memory **shell)
{
	if (!node || !node->content)
		return (1);
	if (ft_strcmp(node->content, ">") == 0)
		return (redirect_out(node, shell, O_WRONLY | O_CREAT | O_TRUNC));
	if (ft_strcmp(node->content, ">>") == 0)
		return (redirect_out(node, shell, O_WRONLY | O_CREAT | O_APPEND));
	if (ft_strcmp(node->content, "<") == 0)
		return (redirect_in(node, shell));
	if (ft_strcmp(node->content, "<<") == 0)
		return (redirect_heredoc(node, shell));
	return (1);
}


static int	read_heredoc_chain(t_tree *node, t_memory **shell)
{
	int	prev_fd;
	int	cur_fd;

	if (node && node->content && ft_strcmp(node->content, "<<") == 0)
	{
		prev_fd = read_heredoc_chain(node->left, shell);
		if (prev_fd < 0)
			return (-1);
		cur_fd = get_heredoc_fd(node->right->argv[0], (*shell)->envi);
		if (cur_fd < 0)
		{
			if (prev_fd > 0)
				close(prev_fd);
			return (-1);
		}
		if (prev_fd > 0)
			close(prev_fd);
		return (cur_fd);
	}
	return (0);
}

static int	redirect_heredoc(t_tree *node, t_memory **shell)
{
	int		saved_fd;
	int		heredoc_fd;
	t_tree	*cmd;
	int		status;

	saved_fd = dup(STDIN_FILENO);
	if (saved_fd < 0)
		return (1);
	heredoc_fd = read_heredoc_chain(node, shell);
	if (heredoc_fd < 0)
	{
		dup2(saved_fd, STDIN_FILENO);
		close(saved_fd);
		return (1);
	}
	if (heredoc_fd > 0)
	{
		if (dup2(heredoc_fd, STDIN_FILENO) < 0)
		{
			close(heredoc_fd);
			dup2(saved_fd, STDIN_FILENO);
			close(saved_fd);
			return (1);
		}
		close(heredoc_fd);
	}
	cmd = node;
	while (cmd && cmd->content && ft_strcmp(cmd->content, "<<") == 0)
		cmd = cmd->left;
	status = executor_execute_ast(cmd, shell);
	dup2(saved_fd, STDIN_FILENO);
	close(saved_fd);
	return (status);
}
