/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:06:11 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 06:44:35 by xoppy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_in_path(const char *cmd, t_envi *env_list)
{
	t_envi	*node;
	char	*path_val;
	char	**dirs;
	size_t	i;

	node = env_list;
	while (node && ft_strcmp(node->env->key, "PATH"))
		node = node->next;
	if (!node || !node->env->values)
		return (NULL);
	dirs = node->env->values;
	i = 0;
	while (dirs[i])
	{
		path_val = ft_triple_strjoin(dirs[i], "/", cmd);
		if (!path_val)
			return (NULL);
		if (access(path_val, X_OK) == 0)
			return (path_val);
		free(path_val);
		i++;
	}
	return (NULL);
}
