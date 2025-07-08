/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:28:35 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 16:39:53 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_out(t_tree *node, t_envi **env_list, int flags);
static int	redirect_in(t_tree *node, t_envi **env_list);
static int	redirect_heredoc(t_tree *node, t_envi **env_list);

int exec_redirect_node(t_tree *node, t_envi **env_list)
{
    if (!node || !node->content)
        return (1);
    if (ft_strcmp(node->content, ">") == 0)
        return (redirect_out(node, env_list,
                            O_WRONLY | O_CREAT | O_TRUNC));
    if (ft_strcmp(node->content, ">>") == 0)
        return (redirect_out(node, env_list,
                            O_WRONLY | O_CREAT | O_APPEND));
    if (ft_strcmp(node->content, "<") == 0)
            return (redirect_in(node, env_list));
    if (ft_strcmp(node->content, "<<") == 0)
            return (redirect_heredoc(node, env_list));
    return (1);
}

static int  redirect_out(t_tree *node, t_envi **env_list, int flags)
{
    int fd;
    int status;

    fd = open(node->right->content, flags, 0644);
    if (fd < 0)
    {
        print_error("minishell: cannot open file\n");
        return (1);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        close(fd);
        return (1);
    }
    close(fd);
    status = executor_execute_ast(node->left, env_list);
    return (status);
}

static int  redirect_in(t_tree *node, t_envi **env_list)
{
    int fd;
    int status;

    fd = open(node->right->content, O_RDONLY);
    if (fd < 0)
    {
        print_error("minishell: cannot open file\n");
        return (1);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close(fd);
        return(1);
    }
    close(fd);
    status = executor_execute_ast(node->left, env_list);
    return (status);
}

static int  redirect_heredoc(t_tree *node, t_envi **env_list)
{
    int heredoc_fd;
    int status;

    heredoc_fd = get_heredoc_fd(node->right->content);
    if (heredoc_fd < 0)
        return (1);
    if (dup2(heredoc_fd, STDIN_FILENO) < 0)
    {
        close(heredoc_fd);
        return (1);
    }
    close(heredoc_fd);
    status = executor_execute_ast(node->left, env_list);
    return (status);
}