/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 13:59:06 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/20 13:50:42 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		four_b(int fd, wchar_t wchar)
{
	ft_putchar_fd(0xF0 | (wchar >> 18), fd);
	ft_putchar_fd(0x80 | ((wchar >> 12) & 0x3F), fd);
	ft_putchar_fd(0x80 | ((wchar >> 6) & 0x3F), fd);
	ft_putchar_fd(0x80 | (wchar & 63), fd);
	return (4);
}

static int		three_b(int fd, wchar_t wchar)
{
	ft_putchar_fd(0xE0 | (wchar >> 12), fd);
	ft_putchar_fd(0x80 | ((wchar >> 6) & 0x3F), fd);
	ft_putchar_fd(0x80 | (wchar & 63), fd);
	return (3);
}

static int		two_b(int fd, wchar_t wchar)
{
	ft_putchar_fd(0xC0 | (wchar >> 6), fd);
	ft_putchar_fd(0x80 | (wchar & 63), fd);
	return (2);
}

static int		one_b(int fd, wchar_t wchar)
{
	ft_putchar_fd(wchar, fd);
	return (1);
}

int				handle_wchar(int fd, wchar_t wchar)
{
	if (!setlocale(LC_ALL, "en_US.UTF-8"))
	{
		return (-1);
	}
	if (wchar < 0x80)
	{
		return (one_b(fd, wchar));
	}
	else if (wchar < 0x800)
	{
		return (two_b(fd, wchar));
	}
	else if (wchar < 0x10000)
	{
		return (three_b(fd, wchar));
	}
	else if (wchar < 0x110000)
	{
		return (four_b(fd, wchar));
	}
	return (0);
}
