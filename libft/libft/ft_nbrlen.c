/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 11:52:19 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 11:24:35 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int			ft_nbrlen_base(int nbr, int base)
{
	int		len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr = -nbr;
		++len;
	}
	while (nbr)
	{
		nbr /= base;
		++len;
	}
	return (len);
}
