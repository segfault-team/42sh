/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:25:16 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/04 09:24:13 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_exit(t_env *e)
{
	if (e->cmd && e->cmd[1])
		e->exit = ft_atoi(e->cmd[1]);
	else
		e->exit = 0;
	e->x = 0;
	if (tcsetattr(0, TCSADRAIN, &TCAPS.save) == -1)
		ft_error(SH_NAME, "cannot reset termios structure", NULL);
}
