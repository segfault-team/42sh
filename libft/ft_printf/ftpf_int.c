/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:50:59 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_width(t_struct *st, int width, int lenght, int precision)
{
	if ((precision - lenght) > 0)
		width -= (precision - lenght);
	else if (precision < 0 && st->stargs.nbr == 0)
		++width;
	if ((st->flags.plus_sign > 0 || st->flags.space > 0) && st->stargs.nbr >= 0)
		--width;
	return (width);
}

static int		precision_int(t_struct *st, int lenght)
{
	int		pcp;

	pcp = st->flags.precision;
	if (st->flags.precision > 0)
	{
		while (pcp > 0 && pcp-- > lenght)
			st->pc += ft_putchar('0');
		return (1);
	}
	else if (st->flags.precision < 0 && st->stargs.nbr == 0)
		return (-1);
	return (1);
}

static int		put_sign(t_struct *st)
{
	if (st->flags.plus_sign && st->stargs.nbr >= 0)
		st->pc += ft_putchar('+');
	else if (st->flags.space && st->stargs.nbr >= 0)
		st->pc += ft_putchar(' ');
	else if (st->stargs.nbr < 0)
		st->pc += ft_putchar('-');
	return (1);
}

static int		left_int(t_struct *st)
{
	int			lenght;

	lenght = nbr_lenght(st->stargs.nbr, 10);
	st->flags.width = get_width(st, st->flags.width, lenght,
			st->flags.precision);
	st->flags.width -= (st->stargs.nbr < 0) ? 1 : 0;
	st->flags.padchar = (st->flags.pad & PAD_ZERO) ? '0' : ' ';
	if (st->flags.padchar == '0')
		put_sign(st);
	padding_left(st, lenght);
	if (st->flags.padchar == ' ')
		put_sign(st);
	return (lenght);
}

int				a_int(t_struct *st)
{
	int		lenght;
	char	*nbr;

	lenght = 0;
	if (*st->format == 'D')
		st->lmod.l = 1;
	conversion_di(st);
	lenght = left_int(st);
	if (precision_int(st, lenght) < 0)
		return (0);
	nbr = ft_imaxtoa_base(st->stargs.nbr, 10, 'a');
	st->pc += ft_putstr(nbr);
	padding_right(st, lenght);
	free(nbr);
	return (1);
}
