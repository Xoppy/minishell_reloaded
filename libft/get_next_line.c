/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc < adi-marc@student.42luxembour    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:44:22 by ituriel           #+#    #+#             */
/*   Updated: 2025/06/03 18:36:03 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buffer_to_stash(t_list **head, int fd)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 0;
	buffer = NULL;
	while (!newline_found(*head))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0 || bytes_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		append_node(head, buffer);
	}
}

void	append_node(t_list **head, char *buffer)
{
	t_list	*new_node;
	t_list	*head_node;

	head_node = head_pos(*head);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (head_node == NULL)
		*head = new_node;
	else
	{
		head_node->next = new_node;
	}
	new_node->str_buf = buffer;
	new_node->next = NULL;
}

char	*rl_creator(t_list *head)
{
	int		total_length;
	char	*return_line;

	if (head == NULL)
		return (NULL);
	total_length = length_to_nl(head);
	return_line = malloc(sizeof(char) * total_length + 1);
	if (!return_line)
		return (NULL);
	stash_to_line(head, return_line);
	return (return_line);
}

void	stash_to_line(t_list *head, char *return_line)
{
	int	i;
	int	j;

	i = 0;
	if (head == NULL)
		return ;
	while (head)
	{
		j = 0;
		while (head->str_buf[j])
		{
			if (head->str_buf[j] == '\n')
			{
				return_line[i++] = '\n';
				return_line[i] = '\0';
				return ;
			}
			return_line[i++] = head->str_buf[j++];
		}
		head = head->next;
	}
	return_line[i] = '\0';
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_to_stash(&head, fd);
	if (head == NULL)
		return (NULL);
	return_line = rl_creator(head);
	refresh_list(&head);
	return (return_line);
}
