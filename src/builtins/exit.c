/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:45:55 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 07:05:10 by adi-marc         ###   ########.fr       */
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
		print_err_prefix("exit");
		ft_putendl_fd("too many arguments", STDERR_FILENO);
		ft_free_shell(shell);
		exit(1);
	}
	if (argc == 2)
	{
		if (!is_numeric(context->argv[1]))
		{
			print_err_prefix("exit");
			ft_putstr_fd(context->argv[1], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd("numeric argument required", STDERR_FILENO);
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
