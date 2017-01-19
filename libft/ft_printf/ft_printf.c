/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:44:39 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:35:05 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_print(t_struct *st, int ret)
{
	while (*st->format)
	{
		if (*st->format == '%')
		{
			++st->format;
			reset_lmod(st);
			if (*st->format == '\0')
				break ;
			parse_flags(st);
			if (parse_lenght_modifier(st))
				++st->format;
			ret = parse_args(st);
			if (ret)
			{
				++st->pc;
				ret = 0;
			}
		}
		else
			st->pc += ft_putchar(*st->format);
		reset_flags(st);
		++st->format;
	}
}

int				ft_printf(const char *format, ...)
{
	t_struct	*st;
	int			pc;

	if ((st = malloc(sizeof(t_struct))) == NULL)
		return (0);
	va_start(st->args, format);
	set_init_st(st, format);
	ft_print(st, 0);
	va_end(st->args);
	pc = st->pc;
	free(st);
	return (pc);
}
