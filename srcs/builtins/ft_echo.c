/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:38:01 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/20 14:33:15 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_echo(t_env *e)
{
	int		i;
	int		nl;

	i = 0;
	if ((nl = ft_strequ(e->cmd[1], "-n")))
		++i;
	while (e->cmd[++i])
	{
		if ((!nl && i == 2) || (i > 2 && i < (int)e->cmd_len))
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(e->cmd[i], 1);
	}
	if (!nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
