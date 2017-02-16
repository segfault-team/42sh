/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:22:32 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/16 11:09:57 by kboddez          ###   ########.fr       */
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
	int		l;

	l = TCAPS.nb_line;
	xputs("cr");
	while (--l)
		xputs("up");
	xputs("cd");
	ft_putstr(e->prompt);
	tputs(e->line, 1, dsh_putchar);
	if (tcaps_check_key(BUF, 27, 91, 65) && TCAPS.hist_move) // arrown up
		tcaps_history_up(e);
	else if (tcaps_check_key(BUF, 27, 91, 66)) // arrow down
			tcaps_history_down(e);
	tcaps_recalc_pos(e);
}

/*
**	INSTRUCTION FOR RIGHT
**		ARROW KEYS
**
*/

void	tcaps_right(t_env *e)
{
	move_right(e);
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
	  	xputs("le");
	    --TCAPS.nb_move;
		tcaps_recalc_pos(e);
	  }
}
