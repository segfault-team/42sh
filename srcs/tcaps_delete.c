/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:27:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/02 13:14:11 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	INSTRUCTION FOR DELETE KEY
**
**		dm: start delete mode
**		le : move left
**		dc : delete char
**		ed: end delete mode
*/

static void	tcaps_del_end(t_env *e)
{
	xputs("dm");
	xputs("le");
	if (TCAPS.nb_move)
		--TCAPS.nb_move;
	tcaps_recalc_pos(e);
	if (TCAPS.nb_col == WS_COL - 1)
		xputs("cd");
	xputs("dc");
	--TCAPS.nb_read;
	xputs("ed");
}

void		tcaps_del(t_env *e)
{
	if (TCAPS.nb_move == TCAPS.nb_read)
		tcaps_del_end(e);
	else
	{
		if (!TCAPS.nb_read && e->line)
		{
			free(e->line);
			e->line = NULL;
		}
		xputs("le");
		--TCAPS.nb_read;
		if (TCAPS.nb_move)
			--TCAPS.nb_move;
		tcaps_putstr(e, e->line);
	}
}
