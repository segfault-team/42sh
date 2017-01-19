/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:46:56 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:10 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		precision_ptr(t_struct *st, int len)
{
	int			pcp;

	pcp = st->flags.precision;
	if (st->flags.precision > 0)
		while (pcp > 0 && pcp-- > len)
			st->pc += ft_putchar('0');
	return (1);
}

int				a_ptr(t_struct *st)
{
	int				len;
	char			*ptr;
	unsigned long	n_ptr;

	n_ptr = (unsigned long)st->stargs.ptr; 
	st->stargs.ptr = (void*)va_arg(st->args, void *);
	len = unbr_lenght(n_ptr, 16);
	ptr = ft_uimaxtoa_base(n_ptr, 16, 'a');
	st->flags.padchar = (st->flags.zero) ? '0' : ' ';
	if (st->flags.padchar == '0')
		st->pc += ft_putstr("0x");
	padding_left(st, len + 2);
	if (st->flags.padchar == ' ')
		st->pc += ft_putstr("0x");
	precision_ptr(st, len);
	if (((long)st->stargs.ptr > 0) ||
			((long)st->stargs.ptr == 0 && st->flags.precision >= 0))
		st->pc += ft_putstr(ptr) + 1;
	padding_right(st, len + 2);
	free(ptr);
	return (1);
}
