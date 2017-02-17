/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 11:40:31 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 10:45:58 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getchar_fd(int fd)
{
	char	c;

	if (1 != read(fd, &c, 1))
		return (-1);
	return ((int)c);
}

int		ft_getchar(void)
{
	return (ft_getchar_fd(0));
}
