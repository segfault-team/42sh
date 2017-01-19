/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:49:37 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:32 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			form_percent(t_struct *st)
{
	st->flags.padchar = (st->flags.zero) ? '0' : ' ';
	padding_left(st, 1);
	ft_putchar(*st->format);
	padding_right(st, 1);
}

void			form_minus(t_struct *st)
{
	st->flags.pad = PAD_RIGHT;
	++st->format;
	parse_flags(st);
}

void			form_plus(t_struct *st)
{
	st->flags.plus_sign = 1;
	++st->format;
	parse_flags(st);
}

void			form_zero(t_struct *st)
{
	st->flags.pad = (st->flags.pad & PAD_RIGHT) ?
		PAD_RIGHT : st->flags.pad | PAD_ZERO;
	st->flags.zero = 1;
	++st->format;
	parse_flags(st);
}

void			form_width(t_struct *st)
{
	while (*st->format >= '0' && *st->format <= '9')
	{
		st->flags.width = (st->flags.width * 10) + (*st->format - '0');
		++st->format;
	}
	parse_flags(st);
}
