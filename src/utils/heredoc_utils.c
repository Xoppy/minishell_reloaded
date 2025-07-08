/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:42:55 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/08 18:43:13 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*heredoc_tmpfile(void)
{
	char	*prefix;
	char	*pid_str;
	char	*path;
	size_t	len;

	prefix = "/tmp/heredoc_";
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (NULL);
	len = ft_strlen(prefix) + ft_strlen(pid_str) + 1;
	path = malloc(len);
	if (!path)
	{
		free(pid_str);
		return (NULL);
	}
	ft_strlcpy(path, prefix, len);
	ft_strlcat(path, pid_str, len);
	free(pid_str);
	return (path);
}

static void	write_heredoc_content(int fd, const char *delim)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0
			&& line[ft_strlen(delim)] == '\n')
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	get_heredoc_fd(const char *delimiter)
{
	char	*tmpfile;
	int		fd;

	tmpfile = heredoc_tmpfile();
	if (!tmpfile)
		return (-1);
	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		free(tmpfile);
		return (-1);
	}
	write_heredoc_content(fd, delimiter);
	close(fd);
	fd = open(tmpfile, O_RDONLY);
	unlink(tmpfile);
	free(tmpfile);
	return (fd);
}