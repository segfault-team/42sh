/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_wstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 10:59:14 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			ft_putwstr_t(wchar_t *wstr, int len)
{
	int				i;
	int				ret;
	int				pc;

	i = 0;
	ret = 0;
	pc = 0;
	while (wstr[i] && ret < len)
	{
		if ((int)(ret + ft_wchar_size(wstr[i])) > len)
			break ;
		if ((pc = handle_wchar(wstr[i])) < 0)
			return (-1);
		ret += pc;
		++i;
	}
	return (ret);
}

int					a_wstr(t_struct *st)
{
	int		pc;
	int		len;

	pc = 0;
	st->stargs.wstr = (wchar_t*)va_arg(st->args, wchar_t *);
	st->stargs.wstr = (st->stargs.wstr) ? st->stargs.wstr : L"(null)";
	len = wstr_lenght(st);
	st->flags.padchar = (st->flags.zero) ? '0' : ' ';
	padding_left(st, len);
	if ((pc = ft_putwstr_t(st->stargs.wstr, len)) < 0)
		return ((st->pc = -1));
	padding_right(st, len);
	st->pc += pc;
	return (0);
}
