/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:28:35 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/23 13:17:32 by cauffret         ###   ########.fr       */
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

static void	restore_fd(int saved_fd, int target_fd)
{
	dup2(saved_fd, target_fd);
	close(saved_fd);
}

static int	redirect_heredoc(t_tree *node, t_memory **shell)
{
	int		saved_stdin;
	int		heredoc_fd;
	int		status;
	t_envi	**env_list;

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
