/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:37:40 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:51 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		reset_lmod(t_struct *st)
{
	st->lmod.hh = 0;
	st->lmod.h = 0;
	st->lmod.ll = 0;
	st->lmod.l = 0;
	st->lmod.j = 0;
	st->lmod.z = 0;
	st->flags.width = 0;
	st->flags.pad = 0;
	st->flags.plus_sign = 0;
	st->flags.space = 0;
}

void		reset_flags(t_struct *st)
{
	st->flags.width = 0;
	st->flags.pad = 0;
	st->flags.padchar = ' ';
	st->flags.precision = 0;
	st->flags.zero = 0;
	st->flags.sharp = 0;
	st->flags.minus = 0;
	st->flags.plus_sign = 0;
	st->flags.space = 0;
}

void		set_init_st(t_struct *st, const char *format)
{
	st->format = format;
	st->stargs.str = NULL;
	st->stargs.ch = 0;
	st->stargs.wstr = NULL;
	st->stargs.nbr = 0;
	st->stargs.ptr = NULL;
	st->pc = 0;
	reset_flags(st);
}
