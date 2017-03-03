/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 18:05:33 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:38:20 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** DESCRIPTION:
**     Allocate (with malloc(3)) and returns a “fresh” string ending
**     with ’\0’ representing the integer n given as argument.
**     Negative numbers must be supported. If the allocation fails,
**     the function returns NULL.
*/

static int		ft_nb_len(unsigned int n)
{
	int		len;

	len = 0;
	if ((int)n < 0)
	{
		n *= -1;
		++len;
	}
	while (n)
	{
		n = n / 10;
		++len;
	}
	return (len);
}

static int		ft_itoa_sign(int n)
{
	return ((n < 0) ? -1 : 1);
}

static char		*ft_itoa_nbc(unsigned int nb, int nb_len, int sign)
{
	char			*nbc;

	if ((nbc = ft_strnew(nb_len)) == NULL)
		return (NULL);
	nbc += (nb_len);
	*nbc = '\0';
	while (nb != 0)
	{
		*--nbc = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (sign == -1)
		*--nbc = '-';
	return (nbc);
}

static char		*ft_itoa_zero(void)
{
	char			*nbc;

	if ((nbc = ft_strnew(2)) == NULL)
		return (NULL);
	nbc[0] = '0';
	nbc[1] = '\0';
	return (nbc);
}

char			*ft_itoa(int n)
{
	int				sign;
	int				nb_len;
	unsigned int	nb;

	if (n == 0)
		return (ft_itoa_zero());
	sign = ft_itoa_sign(n);
	nb = (sign == -1) ? -n : n;
	nb_len = ft_nb_len(nb);
	return (ft_itoa_nbc(nb, nb_len, sign));
}
