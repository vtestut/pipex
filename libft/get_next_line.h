/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:30:31 by vtestut          #+#    #+#             */
/*   Updated: 2022/12/13 16:48:23 by vtestut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_bufferList
{
	char				*content;
	struct s_bufferList	*next;	
}						t_bufferList;

typedef struct s_fdList
{
	int					fd;
	t_bufferList		*begin;
	struct s_fdList		*next_fd;	
}					t_fdList;


char			*get_next_line(int fd);
t_bufferList	*ftlst_new_buffer(void);
t_fdList		*ftlst_new_fd(int fd);
int				end_of_line(char *content);
size_t			count_memory(t_bufferList *current);
t_fdList		*clean_fd_list(t_fdList *fd_list, t_fdList *current);

#endif