/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:11:03 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/25 18:25:56 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_sig;

static void handle_sigint(int signo)
{
    (void)signo;
    g_sig = 130;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void handle_sigquit(int signo)
{
    (void)signo;
}

void    signal_init(void)
{
    struct sigaction    sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = handle_sigquit;
    sigaction(SIGQUIT, &sa, NULL);
}