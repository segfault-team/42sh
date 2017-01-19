/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 13:59:06 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/15 18:26:39 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		four_b(wchar_t wchar)
{
	ft_putchar(0xF0 | (wchar >> 18));
	ft_putchar(0x80 | ((wchar >> 12) & 0x3F));
	ft_putchar(0x80 | ((wchar >> 6) & 0x3F));
	ft_putchar(0x80 | (wchar & 63));
	return (4);
}

static int		three_b(wchar_t wchar)
{
	ft_putchar(0xE0 | (wchar >> 12));
	ft_putchar(0x80 | ((wchar >> 6) & 0x3F));
	ft_putchar(0x80 | (wchar & 63));
	return (3);
}

static int		two_b(wchar_t wchar)
{
	ft_putchar(0xC0 | (wchar >> 6));
	ft_putchar(0x80 | (wchar & 63));
	return (2);
}

static int		one_b(wchar_t wchar)
{
	ft_putchar(wchar);
	return (1);
}

int				handle_wchar(wchar_t wchar)
{
	if (!setlocale(LC_ALL, "en_US.UTF-8"))
	{
		return (-1);
	}
	if (wchar < 0x80)
	{
		return (one_b(wchar));
	}
	else if (wchar < 0x800)
	{
		return (two_b(wchar));
	}
	else if (wchar < 0x10000)
	{
		return (three_b(wchar));
	}
	else if (wchar < 0x110000)
	{
		return (four_b(wchar));
	}
	return (0);
}
