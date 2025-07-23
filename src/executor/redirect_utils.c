/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:05:06 by cauffret          #+#    #+#             */
/*   Updated: 2025/07/23 13:16:44 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int redirect_out_helper(int file_fd, int saved_stdout)
{
    close(file_fd);
    ft_printf("minishell: %s\n", strerror(errno));
    if (dup2(saved_stdout, STDOUT_FILENO) < 0) {
        ft_printf("minishell: critical error restoring stdout: %s\n", strerror(errno));
    }
    close(saved_stdout);
    return (1);
}

int redirect_out(t_tree *node, t_memory **shell, int flags)
{
    int saved_stdout; 
    int file_fd;
    int status;
    
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout < 0) 
    {
        ft_printf("minishell: %s\n", strerror(errno));
        return (1);
    }
    file_fd = open(node->right->content, flags, 0644);
    if (file_fd < 0)
    {
        ft_printf("minishell: %s: %s\n", node->right->content, strerror(errno));
        close(saved_stdout);
        return (1);
    }
    if (dup2(file_fd, STDOUT_FILENO) < 0)
        return redirect_out_helper(file_fd, saved_stdout);
    close(file_fd);
    status = executor_execute_ast(node->left, shell);
    if (dup2(saved_stdout, STDOUT_FILENO) < 0) 
        ft_printf("minishell: critical error restoring stdout: %s\n", strerror(errno));
    close(saved_stdout);
    return status;
}

int	redirect_in(t_tree *node, t_memory **shell)
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
		ft_printf("minishell: %s: %s\n", node->right->content, strerror(errno));
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
