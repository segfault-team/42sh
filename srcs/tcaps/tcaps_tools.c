/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:28:29 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/09 18:53:27 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** RAZ LE BOL DE TOUT REECRIRE !
*/

void	xputs(char *tag)
{
	char	*res;

	res = tgetstr(tag, NULL);
	tputs(res, 1, dsh_putchar);
}

void	move_right(t_env *e)
{
	if (TCAPS.nb_col == (WS_COL - 1))
	{
		xputs("do");
		xputs("cr");
	}
	else
		xputs("nd");
	++TCAPS.nb_move;
	tcaps_recalc_pos(e);
}
