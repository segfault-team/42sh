/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:54 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:54 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	INSTRUCTION FOR UP/DOWN
**		ARROW KEYS
**
**	cr: return at the begining of the line
**  cd: clear the line
*/

void	tcaps_history_first_step(t_env *e)
{
	if (tcaps_check_key(BUF, 27, 91, 65) && HIST_MOVE)
		tcaps_history_up(e);
	else if (tcaps_check_key(BUF, 27, 91, 66))
		tcaps_history_down(e);
	tcaps_recalc_pos(e);
}

/*
**	INSTRUCTION FOR LEFT
**		ARROW KEYS
**
**  le: move cursor once on the left
**  WIN_WIDTH : e->tcaps.ws.ws_col
*/

void	tcaps_left(t_env *e)
{
	if (TCAPS.nb_col > (int)ft_strlen(e->prompt) || TCAPS.nb_line > 1)
	{
		if (TCAPS.nb_col == 0 && TCAPS.nb_line > 1)
			TCAPS.nb_col = WIN_WIDTH;
		xputs(TGETSTR_LE);
		--NB_MOVE;
		tcaps_recalc_pos(e);
	}
}
