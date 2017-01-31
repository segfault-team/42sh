/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:22:32 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/31 10:56:25 by vlistrat         ###   ########.fr       */
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
	char *res;

	res = tgetstr("cr", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("cd", NULL);
	tputs(res, 1, dsh_putchar);
	ft_putstr(e->prompt);
	if (tcaps_check_key(BUF, 27, 91, 65))
		tcaps_history_up(e);
	else
		tcaps_history_down(e);
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
	char	*res;

	if ((TCAPS.nb_line == 1 && TCAPS.nb_col + ft_strlen(e->prompt) == TCAPS.ws.ws_col - 1) ||
	    (TCAPS.nb_line != 1 && TCAPS.nb_col == TCAPS.ws.ws_col - 1))
	  {
	    res = tgetstr("do", NULL);
	    tputs(res, 1, dsh_putchar);
	    res = tgetstr("dr", NULL);
	    TCAPS.nb_col = 0;	    
	  }
	else
	  res = tgetstr("nd", NULL);
	tputs(res, 1, dsh_putchar);
	++TCAPS.nb_move;
	++TCAPS.nb_col;
	tcaps_recalc_pos(e);
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
	char	*res;

	if (TCAPS.nb_col > (int)ft_strlen(e->prompt) || TCAPS.nb_line > 1)
	  {
	    if (TCAPS.nb_col == 0 && TCAPS.nb_line > 1)
	      TCAPS.nb_col = WS_COL;
	    res = tgetstr("le", NULL);
	    tputs(res, 1, dsh_putchar);
	    --TCAPS.nb_move;
	    --TCAPS.nb_col;
		tcaps_recalc_pos(e);
	  }
}
