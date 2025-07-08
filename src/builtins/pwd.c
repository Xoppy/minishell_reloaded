/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:43:26 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 17:45:06 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_pwd(t_exec *context)
{
    char    *cwd;

    (void)context;
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        print_error("pwd: could not retrieve current directory\n");
        return (1);
    }
    ft_printf("%s\n", cwd);
    free(cwd);
    return (0);
}
