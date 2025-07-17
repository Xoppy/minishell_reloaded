/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:48:26 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/17 18:40:46 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int  exec_builtin_cmd(char **argv, t_memory **shell)
{
    t_envi **env_list;
    int result;

    env_list = &(*shell)->envi;
    (*shell)->exec = malloc(sizeof(t_exec));
    (*shell)->exec->argv = argv;
    (*shell)->exec->env = (*env_list);
    (*shell)->exec->status = 0;
    result = executor_run_builtin((*shell)->exec, shell);
    return (result);
}

// Note that WEXITSTATUS and WIFEXITED are not functions but macros
static int  exec_external_cmd(char **argv, t_memory **shell)
{
	char	**envp;
	char	*path;
	pid_t	pid;
	int		status;
    t_envi **env_list;

    env_list = &(*shell)->envi;
	pid = fork();
	if (pid < 0)
    {
        perror("fork");
        return(1);
    }
	if (pid == 0)
	{
		envp = env_list_to_array(*env_list);
		if (ft_strchr(argv[0], '/'))
			path = ft_strdup(argv[0]);
		else
			path = find_in_path(argv[0], *env_list);
		if (!path)
		{
			ft_printf("minishell: %s: command not found\n", argv[0]);
            ft_free_string_array(envp);
			exit(127);
		}
		execve(path, argv, envp);
		ft_printf("minishell: %s: %s\n", argv[0], strerror(errno));
		free(path);
		ft_free_string_array(envp);
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int  exec_simple_cmd(t_tree *node, t_memory **shell)
{
    char    **argv;

    argv = ft_split(node->content, ' ');
    if (!argv)
        return (1);
    if (executor_is_builtin(argv[0]))
        (*shell)->status = exec_builtin_cmd(argv, shell);
    else
        (*shell)->status = exec_external_cmd(argv, shell);
    ft_free_string_array(argv);
    return ((*shell)->status);
}

int executor_execute_ast(t_tree *node, t_memory **shell)
{    
    if (!node)
        return (0);
    if (is_pipe(node->content))
        return (exec_pipe_node(shell, node));
    if (is_redirect(node->content))
        return (exec_redirect_node(node, shell));
    return (exec_simple_cmd(node, shell));
}

int executor_is_builtin(const char *cmd)
{
    if (!cmd)
        return (0);
    return (!strcmp(cmd, "cd")
        || !strcmp(cmd, "echo")
        || !strcmp(cmd, "env")
        || !strcmp(cmd, "export")
        || !strcmp(cmd, "unset")
        || !strcmp(cmd, "pwd")
        || !strcmp(cmd, "exit"));
}

int executor_run_builtin(t_exec *context, t_memory **shell)
{
    if (!context || !context->argv || !context->argv[0])
        return (1);
    if (!strcmp(context->argv[0], "cd"))
        return (builtin_cd(context));
    if (!strcmp(context->argv[0], "echo"))
        return (builtin_echo(context));
    if (!strcmp(context->argv[0], "env"))
        return (builtin_env(context));
    if (!strcmp(context->argv[0], "export"))
        return (builtin_export(context));
    if (!strcmp(context->argv[0], "unset"))
        return (builtin_unset(context));
    if (!strcmp(context->argv[0], "pwd"))
        return (builtin_pwd(context));
    if (!strcmp(context->argv[0], "exit"))
        return (builtin_exit(context, shell));
    return (1);
}
