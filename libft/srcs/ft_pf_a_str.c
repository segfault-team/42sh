/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 10:59:26 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:13 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			a_str(t_struct *st)
{
	int		len;
	int		i;

	i = 0;
	st->stargs.str = (char*)va_arg(st->args, int *);
	st->stargs.str = (st->stargs.str) ? st->stargs.str : "(null)";
	len = str_lenght(st);
	st->flags.padchar = (st->flags.zero) ? '0' : ' ';
	padding_left(st, len);
	if (st->flags.precision == 0)
		st->pc += ft_putstr(st->stargs.str);
	else if (st->flags.precision > 0)
		while (i < st->flags.precision && st->stargs.str[i])
			st->pc += ft_putchar(st->stargs.str[i++]);
	padding_right(st, len);
	return (1);
}
