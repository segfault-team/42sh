/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:41:41 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:42 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			wstr_lenght(t_struct *st)
{
	int		len;

	len = 1;
	if (st->flags.precision == 0)
		len = ft_wstrlen(st->stargs.wstr);
	else if (st->flags.precision < 0)
	{
		len = ft_wstrlen(st->stargs.wstr);
		len = (st->flags.width > 0) ? 0 : len;
	}
	else
	{
		if (st->flags.precision > (int)ft_wstrlen(st->stargs.wstr))
			len = ft_wstrlen(st->stargs.wstr);
		else
		{
			len = st->flags.precision;
			if ((int)ft_wchar_size(st->stargs.wstr[0]) > st->flags.precision)
				len = 1;
			if (st->flags.width > st->flags.precision)
				if (ft_wchar_size(st->stargs.wstr[0]) > 1)
					--len;
		}
	}
	return (len);
}

int			str_lenght(t_struct *st)
{
	int		len;

	len = 0;
	if (st->flags.precision == 0)
		len = ft_strlen(st->stargs.str);
	else if (st->flags.precision < 0)
	{
		len = ft_strlen(st->stargs.str);
		if (st->flags.width > 0)
			len = 0;
		--st->pc;
	}
	else
	{
		if (st->flags.precision > (int)ft_strlen(st->stargs.str))
			len = ft_strlen(st->stargs.str);
		else
			len = st->flags.precision;
		--st->pc;
	}
	return (len);
}

int			nbr_lenght(long long nbr, int base)
{
	int		lenght;

	lenght = 0;
	if (nbr < 0)
		nbr *= -1;
	else if (nbr == 0)
		++lenght;
	while (nbr)
	{
		nbr /= base;
		++lenght;
	}
	return (lenght);
}

int			unbr_lenght(long long nbr, int base)
{
	int		lenght;

	lenght = 0;
	if (nbr == 0)
		++lenght;
	while (nbr)
	{
		nbr /= base;
		++lenght;
	}
	return (lenght);
}
