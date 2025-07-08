/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:43:03 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 18:45:05 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *get_env_value(t_envi *env_list, char *key)
{
    while (env_list)
    {
        if (ft_strcmp(env_list->env->key, key) == 0
            && env_list->env->values
            && env_list->env->values[0])
        {
            return (env_list->env->values[0]);   
        }
        env_list = env_list->next;
    }
    return (NULL);
}

static int  set_env_value(t_envi *env_list, char *key, const char *value)
{
    t_envi  *current;
    char    **new_vals;

    current = env_list;
    while (current)
    {
        if (ft_strcmp(current->env->key, key) == 0)
        {
            ft_free_string_array(current->env->values);
            new_vals = malloc(sizeof *new_vals * 2); // check this
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

// Note : return ((char *)-1) is a sentinel value to be sure that the error is oldpwd
static char *get_target_dir(char *arg, t_envi *env, char *oldpwd)
{
    char    *home;

    if (!arg || arg[0] == '\0')
    {
        home = get_env_value(env, "HOME");
        if (!home)
            return (NULL);
        return (home);
    }
    if (arg[0] == '-' && arg[1] == '\0')
    {
        if (!oldpwd)
            return ((char *)-1);
        ft_printf("%s\n", oldpwd);
        return (oldpwd);
    }
    return (arg);
}

static void update_pwd_env(t_envi *env, char *oldpwd)
{
    char    *curr_pwd;
    
    if (oldpwd)
        set_env_value(env, "OLDPWD", oldpwd);
    curr_pwd = getcwd(NULL, 0);
    if (curr_pwd)
    {
        set_env_value(env, "PWD", curr_pwd);
        free(curr_pwd);
    }
}

int builtin_cd(t_exec *context)
{
    char    *arg;
    char    *oldpwd;
    char    *target;
    int ret;

    arg = context->argv[1];
    oldpwd = get_env_value(context->env, "PWD");
    target = get_target_dir(arg, context->env, oldpwd);
    if (target == NULL)
    {
        print_error("cd: HOME not set\n");
        return (1);
    }
    if (target == (char *)-1)
    {
        print_error("cd: OLDPWD not set\n");
        return (1);
    }
    ret = chdir(target);
    if (ret < 0)
    {
        perror("cd");
        return (1);
    }
    update_pwd_env(context->env, oldpwd);
    return (0);
}
