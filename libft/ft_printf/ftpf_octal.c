/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_octal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:52:31 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:06 by lfabbro          ###   ########.fr       */
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

static int		sharp_octal(t_struct *st)
{
	if (st->flags.sharp)
		st->pc += ft_putchar('0');
	return (1);
}

static int		precision_octal(t_struct *st, int lenght)
{
	int		pcp;

	pcp = st->flags.precision;
	if (pcp < 0 && st->stargs.u_nbr == 0)
		return (-1);
	else if (pcp == 0 && st->stargs.u_nbr == 0 && st->flags.sharp)
		return (-1);
	if (pcp > 0)
	{
		while (pcp > 0 && pcp-- > lenght)
			st->pc += ft_putchar('0');
	}
	return (1);
}

static int		left_octal(t_struct *st)
{
	int			lenght;

	lenght = unbr_lenght(st->stargs.u_nbr, 8);
	lenght += (st->flags.sharp) ? 1 : 0;
	st->flags.width = get_width(st->flags.width, lenght, st->flags.precision);
	st->flags.padchar = (st->flags.pad & PAD_ZERO) ? '0' : ' ';
	if (st->flags.padchar == '0')
	{
		sharp_octal(st);
	}
	padding_left(st, lenght);
	if (st->flags.padchar == ' ')
	{
		sharp_octal(st);
	}
	return (lenght);
}

int				a_octal(t_struct *st)
{
	int		lenght;
	char	*oct;

	lenght = 0;
	if (*st->format == 'O')
		st->lmod.l = 1;
	conversion_oux(st);
	lenght = left_octal(st);
	if (precision_octal(st, lenght) < 0)
		return (0);
	oct = ft_uimaxtoa_base(st->stargs.u_nbr, 8, 'a');
	st->pc += ft_putstr(oct);
	padding_right(st, lenght);
	free(oct);
	return (1);
}
