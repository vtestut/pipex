/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 05:38:33 by vtestut          #+#    #+#             */
/*   Updated: 2023/06/08 18:52:26 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	DESCRIPTION :
	The function ft_putchar_fd writes the given character to the given
	file descriptor.

	RETURN VALUE :
	None.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
