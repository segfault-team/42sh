/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 13:11:48 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:48 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		parse_flags(t_struct *st)
{
	if (*st->format == '%')
		form_percent(st);
	else if (*st->format == '#')
		form_sharp(st);
	else if (*st->format == '-')
		form_minus(st);
	else if (*st->format == '+')
		form_plus(st);
	else if (*st->format == ' ')
		form_space(st);
	else if (*st->format == '0')
		while (*st->format == '0')
			form_zero(st);
	else if (*st->format == '.')
		form_precision(st);
	else if (*st->format > '0' && *st->format <= '9')
		form_width(st);
}

int			parse_lenght_modifier(t_struct *st)
{
	if (*st->format == 'h')
	{
		if (*(st->format + 1) == 'h')
		{
			++st->format;
			return (st->lmod.hh = 1);
		}
		else
			return (st->lmod.h = 1);
	}
	else if (*st->format == 'l')
	{
		if (*(st->format + 1) == 'l')
		{
			++st->format;
			return (st->lmod.ll = 1);
		}
		else
			return (st->lmod.l = 1);
	}
	else if (*st->format == 'j')
		return (st->lmod.j = 1);
	else if (*st->format == 'z')
		return (st->lmod.z = 1);
	return (0);
}

int			parse_args(t_struct *st)
{
	if (*st->format == 'd' || *st->format == 'i' || *st->format == 'D')
		return (a_int(st));
	else if (*st->format == 'x')
		return (a_hex(st, 'a'));
	else if (*st->format == 'X')
		return (a_hex(st, 'A'));
	else if (*st->format == 'u' || *st->format == 'U')
		return (a_uint(st));
	else if (*st->format == 'o' || *st->format == 'O')
		return (a_octal(st));
	else if (*st->format == '%')
		return (1);
	else if (*st->format == 's' && !st->lmod.l)
		return (a_str(st));
	else if ((*st->format == 'S') || (*st->format == 's' && st->lmod.l))
		return (a_wstr(st));
	else if (*st->format == 'c' && !st->lmod.l)
		return (a_char(st, 1));
	else if ((*st->format == 'C') || (*st->format == 'c' && st->lmod.l))
		return (a_wchar(st));
	else if (*st->format == 'p')
		return (a_ptr(st));
	else
		return (a_char(st, 0));
}
