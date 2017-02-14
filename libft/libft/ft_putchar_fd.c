/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 18:53:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/20 13:44:07 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Outputs the char c to the file descriptor fd.
*/

int		ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
