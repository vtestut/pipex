/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:27:50 by vtestut           #+#    #+#             */
/*   Updated: 2023/06/12 18:57:52 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

typedef struct s_data
{
	char	**envp;
	char	**av;
	int		ac;
	int		heredoc;
	int		fd_in;
	int		fd_out;
	int		*pipe;
	int		nb_cmds;
	int		child;
	int		*pids;
	char	**cmd_options;
	char	*cmd_path;
}		t_data;

//			02_INITILISATION.C
t_data	init(int ac, char **av, char **envp);

//			03_PARSING.c
char	*get_cmd(char *cmd, t_data *data);

//			04_SET_FILES.C
void	get_input_file(t_data *data);
void	get_output_file(t_data *data);
void	get_heredoc(t_data *data);

//			05_UTILS.C
void	exit_error(int error_status, t_data *data);
int		msg(char *str1, char *str2, char *str3, int erno);
void	close_fds(t_data *data);
void	free_strs(char *str, char **strs);

#endif