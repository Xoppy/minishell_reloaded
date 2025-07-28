/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-marc < adi-marc@student.42luxembour    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:42:55 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 06:44:27 by xoppy            ###   ########.fr       */
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
	FILE	*saved_out;
	char	*line;
	char	*exp;

	saved_out = rl_outstream;
	rl_outstream = stderr;
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
		exp = expand_token(line, env_list, 0);
		free(line);
		write(write_fd, exp, ft_strlen(exp));
		write(write_fd, "\n", 1);
		free(exp);
	}
	rl_outstream = saved_out;
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
