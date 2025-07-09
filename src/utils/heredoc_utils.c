/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc <adi-marc@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:42:55 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/09 13:44:59 by adi-marc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*heredoc_tmpfile(void)
{
	char	*prefix;
	char	*pid_str;
	char	*path;
	size_t	total_len;

	prefix = "/tmp/minishell_heredoc_";
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (NULL);
	total_len = ft_strlen(prefix) + ft_strlen(pid_str) + 1;
	path = malloc(total_len);
	if (!path)
	{
		free(pid_str);
		return (NULL);
	}
	ft_strlcpy(path, prefix, total_len);
	ft_strlcat(path, pid_str, total_len);
	free(pid_str);
	return (path);
}

static void	write_heredoc_content(int write_fd, char *delimiter,
									t_envi *env_list)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		/* expand $VAR inside the heredoc line */
		expanded = expand_token(line, env_list, 0);
		free(line);
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		free(expanded);
	}
}

int	get_heredoc_fd(char *delimiter, t_envi *env_list)
{
	char	*tmpfile;
	int		write_fd;
	int		read_fd;

	tmpfile = heredoc_tmpfile();
	if (!tmpfile)
		return (-1);
	write_fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (write_fd < 0)
	{
		free(tmpfile);
		return (-1);
	}
	write_heredoc_content(write_fd, delimiter, env_list);
	close(write_fd);
	read_fd = open(tmpfile, O_RDONLY);
	unlink(tmpfile);
	free(tmpfile);
	return (read_fd);
}
