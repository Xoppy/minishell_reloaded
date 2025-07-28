/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:25:50 by ituriel           #+#    #+#             */
/*   Updated: 2025/07/28 13:28:02 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_slash_cmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (0);
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	return (1);
}

static int	handle_lookup_cmd(char *cmd, t_envi *env_list)
{
	char	*path;

	path = find_in_path(cmd, env_list);
	if (path)
	{
		free(path);
		return (0);
	}
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (1);
}

int	check_cmd(char *cmd, t_memory **shell)
{
	if (executor_is_builtin(cmd))
		return (0);
	if (!cmd)
	{
		write(2, "\n", 1);
		return (1);
	}
	if (ft_strchr(cmd, '/'))
		return (handle_slash_cmd(cmd));
	return (handle_lookup_cmd(cmd, (*shell)->envi));
}
