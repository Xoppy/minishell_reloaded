/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc < adi-marc@student.42luxembour    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:43:03 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/09 16:16:21 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value(t_envi *env_list, char *key)
{
	t_envi	*current;

	current = env_list;
	while (current)
	{
		if (!ft_strcmp(current->env->key, key)
			&& current->env->values && current->env->values[0])
			return (current->env->values[0]);
		current = current->next;
	}
	return (NULL);
}

static int	set_env_value(t_envi *env_list, char *key, char *value)
{
	t_envi	*current;
	char	**new_vals;

	current = env_list;
	while (current)
	{
		if (!ft_strcmp(current->env->key, key))
		{
			ft_free_string_array(current->env->values);
			new_vals = malloc(sizeof(*new_vals) * 2);
			if (!new_vals)
				return (1);
			new_vals[0] = ft_strdup(value);
			new_vals[1] = NULL;
			current->env->values = new_vals;
			return (0);
		}
		current = current->next;
	}
	return (1);
}

static char	*determine_target(const char *arg, t_envi *env_list, char **oldpwd_ptr)
{
	char	*home;

	if (!arg || arg[0] == '\0')
	{
		home = get_env_value(env_list, "HOME");
		return (home);
	}
	if (arg[0] == '-' && arg[1] == '\0')
	{
		*oldpwd_ptr = get_env_value(env_list, "OLDPWD");
		if (!*oldpwd_ptr)
			return ((char *)-1);
		ft_printf("%s\n", *oldpwd_ptr);
		return (*oldpwd_ptr);
	}
	return ((char *)arg);
}

static void	update_pwd_env(t_envi *env_list, char *prev_pwd)
{
	char	*cwd;

	if (prev_pwd)
		set_env_value(env_list, "OLDPWD", prev_pwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		set_env_value(env_list, "PWD", cwd);
		free(cwd);
	}
}

int	builtin_cd(t_exec *context)
{
	char	*arg;
	char	*oldpwd;
	char	*target;
	int		ret;

	arg = context->argv[1];
	oldpwd = get_env_value(context->env, "PWD");
	target = determine_target(arg, context->env, &oldpwd);
	if (!target)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (target == (char *)-1)
	{
		ft_printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	ret = chdir(target);
	if (ret < 0)
	{
		ft_printf("minishell: cd: %s: %s\n", target, strerror(errno));
		return (1);
	}
	update_pwd_env(context->env, oldpwd);
	return (0);
}
