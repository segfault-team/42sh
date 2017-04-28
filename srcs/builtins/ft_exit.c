/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:09:25 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/28 18:09:25 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_exit(t_env *e, char **cmd)
{
	if (cmd && cmd[1])
	{
		if (!ft_strisdigit(cmd[1]))
		{
			e->exit = 255;
			ft_error("exit", cmd[1], "numeric argument required");
		}
		else if (ft_tablen(cmd) > 2)
		{
			ft_error("exit", "too many arguments", NULL);
			return (-1);
		}
		else
			e->exit = ft_atoi(cmd[1]);
	}
	else
		e->exit = 0;
	e->x = 0;
	if (tcaps_reset(e) && !e->raw)
		ft_error("cannot reset termios structure", NULL, NULL);
	return (0);
}
