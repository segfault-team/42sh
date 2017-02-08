/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:22:32 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/08 13:31:39 by vlistrat         ###   ########.fr       */
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

void	tcaps_history(t_env *e)
{
	int		l;

	l = TCAPS.nb_line;
	xputs("cr");
	while (--l)
		xputs("up");
//	clear_cmd(e);
	xputs("cd");
	ft_putstr(e->prompt);
	tputs(e->line, 1, dsh_putchar);
	if (tcaps_check_key(BUF, 27, 91, 65) && TCAPS.hist_move)
	{
		if (TCAPS.hist_move == -1)
			TCAPS.hist_move = (int)ft_tablen(e->history) - 1;
		else if (TCAPS.hist_move > 0)
			--TCAPS.hist_move;
		tcaps_history_up(e);
	}
	else if (tcaps_check_key(BUF, 27, 91, 66))
	{
		if (TCAPS.hist_move < (int)ft_tablen(e->history) && TCAPS.hist_move != -1)
			++TCAPS.hist_move;
		if (TCAPS.hist_move == (int)ft_tablen(e->history))
		{
			clear_cmd(e);
			TCAPS.hist_move = -1;
		}
		else if (e->line)
			tcaps_history_down(e);
	}
	tcaps_recalc_pos(e);
}

/*
**	INSTRUCTION FOR RIGHT
**		ARROW KEYS
**
**  nd: move cursor once on the right
*/

void	tcaps_right(t_env *e)
{
/*	if (TCAPS.nb_col == TCAPS.ws.ws_col - 1)
	  {
		xputs("do");
		xputs("cr");
	    TCAPS.nb_col = 0;
	  }
	else
		xputs("nd");
	++TCAPS.nb_move;
	tcaps_recalc_pos(e);*/
	move_right(e);
}

/*
**	INSTRUCTION FOR LEFT
**		ARROW KEYS
**
**  le: move cursor once on the left
**  WS_COL : e->tcaps.ws.ws_col
*/

void	tcaps_left(t_env *e)
{
	if (TCAPS.nb_col > (int)ft_strlen(e->prompt) || TCAPS.nb_line > 1)
	  {
	    if (TCAPS.nb_col == 0 && TCAPS.nb_line > 1)
	      TCAPS.nb_col = WS_COL;
	  	xputs("le");
	    --TCAPS.nb_move;
		tcaps_recalc_pos(e);
	  }
}
