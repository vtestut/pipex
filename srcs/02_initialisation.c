/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_initilisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:09:22 by vtestut           #+#    #+#             */
/*   Updated: 2023/06/12 17:51:59 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_data	clean_init(void)
{
	t_data	data;

	data.envp = NULL;
	data.ac = -1;
	data.av = NULL;
	data.heredoc = 0;
	data.fd_in = -1;
	data.fd_out = -1;
	data.pipe = NULL;
	data.nb_cmds = -1;
	data.child = -1;
	data.pids = NULL;
	data.cmd_options = NULL;
	data.cmd_path = NULL;
	return (data);
}

static void	generate_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->pipe + 2 * i) == -1)
			exit_error(msg("Pipe creation failed", "", "", 1), data);
		i++;
	}
}

t_data	init(int ac, char **av, char **envp)
{
	t_data	data;

	data = clean_init();
	data.envp = envp;
	data.ac = ac;
	data.av = av;
	if (!ft_strncmp("here_doc", av[1], 9))
		data.heredoc = 1;
	get_input_file(&data);
	get_output_file(&data);
	data.nb_cmds = ac - 3 - data.heredoc;
	data.pids = malloc(sizeof * data.pids * data.nb_cmds);
	if (!data.pids)
		exit_error(msg("PID error", strerror(errno), "", 1), &data);
	data.pipe = malloc(sizeof * data.pipe * 2 * (data.nb_cmds - 1));
	if (!data.pipe)
		exit_error(msg("Pipe error", "", "", 1), &data);
	generate_pipes(&data);
	return (data);
}
