/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:52:21 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 07:19:39 by xoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(const char *msg)
{
	while (*msg)
	{
		write(STDERR_FILENO, msg, 1);
		msg++;
	}
}

void	print_message(const char *msg)
{
	while (*msg)
	{
		write(STDOUT_FILENO, msg, 1);
		msg++;
	}
}

void	print_err_prefix(char *s)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
}
