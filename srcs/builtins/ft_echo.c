/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:10:47 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:10:47 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_echo_check(char *str)
{
	if (*str == '-')
		str++;
	else
		return (0);
	if (!*str)
		return (0);
	while (*str && *str == 'n')
		str++;
	if (!*str)
		return (1);
	return (0);
}

int			ft_echo(char **args)
{
	int cr;
	int i;
	int len;

	cr = 1;
	i = 1;
	len = ft_tablen(args);
	if (len > 1)
	{
		while (args[i] && ft_echo_check(args[i]))
		{
			cr = 0;
			i++;
		}
		while (i < len)
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
			i++;
			if (len > i)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (cr)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
