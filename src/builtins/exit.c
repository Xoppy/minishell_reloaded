/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauffret <cauffret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:45:55 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/23 12:26:30 by cauffret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(const char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

static void	exit_case(t_exec *context, t_memory **shell, int argc, long *code)
{
	if (argc > 2)
	{
		ft_printf("minishell: exit: too many arguments\n");
		ft_free_shell(shell);
		exit(1);
	}
	if (argc == 2)
	{
		if (!is_numeric(context->argv[1]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				context->argv[1]);
			ft_free_shell(shell);
			exit(2);
		}
		*code = ft_atol(context->argv[1]) & 0xFF;
	}
}

int	builtin_exit(t_exec *context, t_memory **shell)
{
	int		argc;
	long	code;

	argc = 0;
	while (context->argv[argc])
		argc++;
	write(STDOUT_FILENO, "exit\n", 5);
	exit_case(context, shell, argc, &code);
	if (argc != 2 && argc < 2)
		code = context->status & 0xFF;
	ft_free_shell(shell);
	exit(code);
}
