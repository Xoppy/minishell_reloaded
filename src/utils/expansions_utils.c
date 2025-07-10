/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc < adi-marc@student.42luxembour    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:25:28 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/10 11:29:06 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	toggle_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !*in_double)
	{
		*in_single = !*in_single;
		return (1);
	}
	if (c == '"' && !*in_single)
	{
		*in_double = !*in_double;
		return (1);
	}
	return (0);
}