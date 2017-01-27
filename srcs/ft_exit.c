/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:25:16 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/27 10:46:03 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_exit(t_env *e)
{
	char	*res;

//	if (e->cmd[1])
//		e->exit = ft_atoi(e->cmd[1]);
//	else
		e->exit = 0;
//	if (e->cmd[1])
	e->x = 0;
//	tcgetattr(0, &TCAPS.save);
//	TCAPS.save.c_lflag = (ICANON | ECHO);
//	tcsetattr(0, 0, &TCAPS.save);
	TCAPS.termos.c_lflag = (ICANON | ECHO);
	res = tgetstr("ei", NULL);
	tputs(res, 0, dsh_putchar);
	tcsetattr(0, 0, &TCAPS.termos);
//	exit(0);
}
