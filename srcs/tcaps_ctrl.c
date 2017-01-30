/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 14:30:00 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/30 14:32:33 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  INSTRUCTION FOR "Ctrl + l" KEYS
**
**  cl: clear active window
*/

void	tcaps_clear(t_env *e)
{
	char	*res;

	res = tgetstr("cl", NULL);
	tputs(res, 1, dsh_putchar);
	ft_putstr(e->prompt);
}

/*
**  INSTRUCTION FOR "Ctrl + a" KEYS
**
**  cr: return at the begining of the line
**	nd: move cursor once on the right
*/

void	tcaps_rtrbeg(t_env *e)
{
	char	*res;
	int		i;

	res = tgetstr("cr", NULL);
	tputs(res, 1, dsh_putchar);
	i = ft_strlen(e->prompt);
	while (i--)
	{
		res = tgetstr("nd", NULL);
		tputs(res, 1, dsh_putchar);
	}
	TCAPS.nb_move = 0;
}