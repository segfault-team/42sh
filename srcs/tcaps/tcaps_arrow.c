/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:22:32 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/20 18:02:34 by lfabbro          ###   ########.fr       */
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
	if (tcaps_check_key(BUF, 27, 91, 65) && TCAPS.hist_move) // arrown up
		tcaps_history_up(e);
	else if (tcaps_check_key(BUF, 27, 91, 66)) // arrow down
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
	    --TCAPS.nb_move;
		tcaps_recalc_pos(e);
	  }
}
