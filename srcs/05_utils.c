/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:03:11 by vtestut           #+#    #+#             */
/*   Updated: 2023/06/12 00:21:34 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pipe_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->nb_cmds - 1) * 2)
	{
		close(data->pipe[i]);
		i++;
	}
}

void	exit_error(int error_status, t_data *data)
{
	if (data)
	{
		close_fds(data);
		if (data->pipe != NULL)
			free(data->pipe);
		if (data->pids != NULL)
			free(data->pids);
		if (data->cmd_options != NULL || data->cmd_path != NULL)
			free_strs(data->cmd_path, data->cmd_options);
	}
	if (data->heredoc == 1)
		unlink("heredoc.tmp");
	exit(error_status);
}

int	msg(char *str1, char *str2, char *str3, int erno)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
	return (erno);
}

void	close_fds(t_data *data)
{
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	close_pipe_fds(data);
}

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}
