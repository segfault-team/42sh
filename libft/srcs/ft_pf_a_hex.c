/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:50:17 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:01 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_width(int width, int lenght, int precision)
{
	if ((precision - lenght) > 0)
		width -= (precision - lenght);
	else if (precision < 0)
		++width;
	return (width);
}

static int		precision_hex(t_struct *st, int lenght)
{
	int		pcp;

	pcp = st->flags.precision;
	if (st->flags.precision > 0)
	{
		while (pcp > 0 && pcp-- > lenght)
			st->pc += ft_putchar('0');
		if (st->stargs.u_nbr == 0 && st->flags.width <= 0)
			return (0);
		return (1);
	}
	else if (st->flags.precision < 0 && st->stargs.u_nbr == 0)
		return (-1);
	return (1);
}

static int		sharp_hex(t_struct *st, int set)
{
	if (st->flags.sharp)
		if (st->stargs.u_nbr != 0)
		{
			if (set == 'a')
				st->pc += ft_putstr("0x") + 1;
			else if (set == 'A')
				st->pc += ft_putstr("0X") + 1;
		}
	return (1);
}

static int		left_hex(t_struct *st, int set)
{
	int		lenght;

	lenght = unbr_lenght(st->stargs.u_nbr, 16);
	st->flags.width = get_width(st->flags.width, lenght, st->flags.precision);
	st->flags.padchar = (st->flags.pad & PAD_ZERO) ? '0' : ' ';
	lenght += (st->flags.sharp && st->stargs.u_nbr != 0 &&
			st->flags.precision <= 0) ? 2 : 0;
	if (st->flags.padchar == '0')
		sharp_hex(st, set);
	padding_left(st, lenght);
	if (st->flags.padchar == ' ')
		sharp_hex(st, set);
	return (lenght);
}

int				a_hex(t_struct *st, char set)
{
	int		lenght;
	char	*hex;

	conversion_oux(st);
	lenght = left_hex(st, set);
	if (precision_hex(st, lenght) < 0)
		return (0);
	hex = ft_uimaxtoa_base(st->stargs.u_nbr, 16, set);
	st->pc += ft_putstr(hex);
	padding_right(st, lenght);
	free(hex);
	return (1);
}
