/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:28:34 by vtestut           #+#    #+#             */
/*   Updated: 2023/06/12 17:34:25 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_io(int input, int output, t_data *d)
{
	if (dup2(input, STDIN_FILENO) == -1)
		exit_error(1, d);
	if (dup2(output, STDOUT_FILENO) == -1)
		exit_error(1, d);
}

static void	child(t_data *d)
{
	if (d->child == 0)
		redirect_io(d->fd_in, d->pipe[1], d);
	else if (d->child == d->nb_cmds - 1)
		redirect_io(d->pipe[2 * d->child - 2], d->fd_out, d);
	else
		redirect_io(d->pipe[2 * d->child - 2], d->pipe[2 * d->child + 1], d);
	close_fds(d);
	if (d->cmd_options == NULL || d->cmd_path == NULL)
		exit_error(1, d);
	if (execve(d->cmd_path, d->cmd_options, d->envp) == -1)
		exit_error(msg(d->cmd_options[0], ": ", strerror(errno), 1), d);
}

static int	parent(t_data *d)
{
	pid_t	wpid;
	int		status;
	int		exit_code;

	close_fds(d);
	d->child--;
	exit_code = 1;
	while (d->child >= 0)
	{
		wpid = waitpid(d->pids[d->child], &status, 0);
		if (wpid == d->pids[d->nb_cmds - 1])
		{
			if ((d->child == (d->nb_cmds - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		d->child--;
	}
	free(d->pipe);
	free(d->pids);
	return (exit_code);
}

static int	pipex(t_data *d)
{
	int		exit_code;

	if (pipe(d->pipe) == -1)
		exit_error(msg("pipe", ": ", strerror(errno), 1), d);
	d->child = 0;
	while (d->child < d->nb_cmds)
	{
		d->cmd_options = ft_split(d->av[d->child + 2 + d->heredoc], ' ');
		if (!d->cmd_options)
			exit_error(msg("unexpected error", "", "", 1), d);
		d->cmd_path = get_cmd(d->cmd_options[0], d);
		d->pids[d->child] = fork();
		if (d->pids[d->child] == -1)
			exit_error(msg("fork", ": ", strerror(errno), 1), d);
		else if (d->pids[d->child] == 0)
			child(d);
		free_strs(d->cmd_path, d->cmd_options);
		d->child++;
	}
	exit_code = parent(d);
	if (d->heredoc == 1)
		unlink("heredoc.tmp");
	return (exit_code);
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;
	int		exit_code;

	if (ac < 5)
	{
		if (ac >= 2 && !ft_strncmp("here_doc", av[1], 9))
			return (msg("Usage: ", "wrong prompt", "", 1));
		return (msg("Usage: ", "wrong prompt", "", 1));
	}
	else if (ac < 6 && !ft_strncmp("here_doc", av[1], 9))
		return (msg("Usage: ", "wrong prompt", "", 1));
	if (!envp || envp[0][0] == '\0')
		exit_error(msg("Unexpected error.", "", "", 1), &d);
	d = init(ac, av, envp);
	exit_code = pipex(&d);
	return (exit_code);
}
