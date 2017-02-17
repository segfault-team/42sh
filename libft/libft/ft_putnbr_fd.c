/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:09:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/20 13:49:36 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**      Outputs the integer n to the file descriptor fd
*/

int		ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	int				len;

	nb = n;
	len = 0;
	if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		len += ft_putchar_fd(nb + '0', fd);
	return (len);
}
