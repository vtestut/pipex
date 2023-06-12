/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_set_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:46:49 by vtestut           #+#    #+#             */
/*   Updated: 2023/06/12 17:52:54 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_input_file(t_data *d)
{
	if (d->heredoc == 1)
	{
		get_heredoc(d);
		d->fd_in = open("heredoc.tmp", O_RDONLY);
		if (d->fd_in == -1)
			exit_error(msg("here_doc", ": ", strerror(errno), 1), d);
	}
	else
	{
		d->fd_in = open(d->av[1], O_RDONLY, 644);
		if (d->fd_in == -1)
			msg(strerror(errno), ": ", d->av[1], 1);
	}
}

void	get_output_file(t_data *d)
{
	if (d->heredoc == 1)
		d->fd_out = open(d->av[d->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		d->fd_out = open(d->av[d->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fd_out == -1)
		msg(strerror(errno), ": ", d->av[d->ac - 1], 1);
}

void	get_heredoc(t_data *d)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;

	tmp_fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	stdin_fd = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		exit_error(msg("here_doc", ": ", strerror(errno), 1), d);
	line = "";
	while (1)
	{
		ft_putstr_fd("here_doc > ", 1);
		line = get_next_line(stdin_fd);
		if (line == NULL || !ft_strncmp(line, "LIMITER", 7))
			break ;
		if (ft_strlen(d->av[2]) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, d->av[2], ft_strlen(d->av[2] + 1)))
			close(stdin_fd);
		else
			ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	free(line);
	close(tmp_fd);
}
