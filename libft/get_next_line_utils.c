/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc < adi-marc@student.42luxembour    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:44:19 by ituriel           #+#    #+#             */
/*   Updated: 2025/06/03 18:38:25 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	refresh_list(t_list **list)
{
	t_list	*head_node;
	t_list	*new_node;
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	new_node = malloc(sizeof(t_list));
	if (!buffer || !new_node)
		return ;
	head_node = head_pos(*list);
	while (head_node->str_buf[i] && head_node->str_buf[i] != '\n')
		++i;
	while (head_node->str_buf[i] && head_node->str_buf[++i])
		buffer[j++] = head_node->str_buf[i];
	buffer[j] = '\0';
	new_node->str_buf = buffer;
	new_node->next = NULL;
	cleanup_list(list, new_node, buffer);
}

t_list	*head_pos(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

void	cleanup_list(t_list **list, t_list *new_node, char *buffer)
{
	t_list	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (new_node->str_buf[0] != '\0')
		*list = new_node;
	else
	{
		free(buffer);
		free(new_node);
	}
}

size_t	length_to_nl(t_list *head)
{
	size_t	total_length;
	size_t	i;

	total_length = 0;
	if (head == NULL)
	{
		return (0);
	}
	while (head)
	{
		i = 0;
		while (head->str_buf[i])
		{
			if (head->str_buf[i] == '\n')
			{
				total_length++;
				return (total_length);
			}
			total_length++;
			i++;
		}
		head = head->next;
	}
	return (total_length);
}

int	newline_found(t_list *head)
{
	int	i;

	i = 1;
	if (head == NULL)
	{
		return (0);
	}
	while (head)
	{
		i = 0;
		while (head->str_buf[i] && i < BUFFER_SIZE)
		{
			if (head->str_buf[i] == '\n')
			{
				return (1);
			}
			i++;
		}
		head = head->next;
	}
	return (0);
}
