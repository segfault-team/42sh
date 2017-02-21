/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:38:01 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/21 15:24:27 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_echo(t_env *e, char **cmd)
{
	int		i;
	int		nl;
	size_t	cmd_len;

	i = 0;
	if (e)
		;
	cmd_len = ft_tablen(cmd);
	if ((nl = ft_strequ(cmd[1], "-n")))
		++i;
	while (cmd[++i])
	{
		if ((!nl && i == 2) || (i > 2 && i < (int)cmd_len))
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd[i], 1);
	}
	if (!nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
