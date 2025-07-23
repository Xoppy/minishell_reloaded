/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:30:34 by cauffret          #+#    #+#             */
/*   Updated: 2025/07/23 13:00:53 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executor_is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (!strcmp(cmd, "cd") || !strcmp(cmd, "echo") || !strcmp(cmd, "env")
		|| !strcmp(cmd, "export") || !strcmp(cmd, "unset") || !strcmp(cmd,
			"pwd") || !strcmp(cmd, "exit"));
}

int	executor_run_builtin(t_exec *context, t_memory **shell)
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

static void	free_no_path(t_memory **shell, char **argv, char **envp)
{
	ft_printf("minishell: %s: command not found\n", argv[0]);
	ft_free_shell(shell);
	ft_free_string_array(envp);
	ft_free_string_array(argv);
	exit(127);
}

static void	free_no_execve(char *path, t_memory **shell, char **envp,
		char **argv)
{
	ft_printf("minishell: %s: %s\n", argv[0], strerror(errno));
	free(path);
	ft_free_shell(shell);
	ft_free_string_array(envp);
	ft_free_string_array(argv);
	exit(126);
}

void	child_process(char **argv, t_memory **shell)
{
	t_envi	*env_list;
	char	**envp;
	char	*path;

	env_list = (*shell)->envi;
	envp = env_list_to_array(env_list);
	if (ft_strchr(argv[0], '/'))
		path = ft_strdup(argv[0]);
	else
		path = find_in_path(argv[0], env_list);
	if (!path)
		free_no_path(shell, argv, envp);
	execve(path, argv, envp);
	free_no_execve(path, shell, envp, argv);
}
