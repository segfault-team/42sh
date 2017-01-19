/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_char.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 10:59:21 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:25:57 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			a_char(t_struct *st, int va)
{
	if (va)
	{
		if (st->lmod.h || st->lmod.hh || st->lmod.l || st->lmod.ll ||
				st->lmod.j || st->lmod.z)
			return ((st->pc = -1));
		else
			st->stargs.ch = (unsigned char)va_arg(st->args, int);
	}
	else
		st->stargs.ch = *st->format;
	st->flags.padchar = (st->flags.zero == 1) ? '0' : ' ';
	padding_left(st, 1);
	ft_putchar(st->stargs.ch);
	padding_right(st, 1);
	return (1);
}
