/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:00:50 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 17:04:20 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_echo(t_exec *context)
{
    int i;
    int nflag;
    ssize_t w;

    i = 1;
    nflag = 0;
    while(context->argv[i] && ft_strcmp(context->argv[i], "-n") == 0)
    {
        nflag = 1;
        i++;
    }
    while(context->argv[i])
    {
        w = write(STDOUT_FILENO, context->argv[i], ft_strlen(context->argv[i]));
        if (w < 0)
            return (1);
        if (context->argv[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!nflag)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
