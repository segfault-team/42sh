/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:27:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/04 12:49:28 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tcaps_del_fwd(t_env *e)
{
	char	buf[3];

	ft_bzero(buf, 3);
	if (BUF[0] != CTRL_D)
		read(0, buf, 3);
	else
		buf[0] = 126;
	if (tcaps_check_key(buf, 126, 0, 0) && NB_READ && NB_MOVE != NB_READ)
	{
		xputs("dm");
		xputs("dc");
		xputs("ed");
		++NB_MOVE;
		if (!(NB_READ - 1))
			strfree(&e->line);
		e->line = ft_realloc_delete_char(e);
		--NB_MOVE;
		if (!NB_READ && e->line)
			strfree(&e->line);
		--NB_READ;
		tcaps_putstr(e, e->line);
	}
}

/*
 **	INSTRUCTIONS FOR DELETES KEYS
 **
 **		tcaps_del_bkw : BACKSPACE
 **		tcaps_del_fwd : DELETE
 **
 **		dm: start delete mode
 **		le : move left
 **		nd : move right
 **		dc : delete char
 **		ed: end delete mode
 */

static void	tcaps_del_bkw_end(t_env *e)
{
	xputs("dm");
	xputs("le");
	if (TCAPS.nb_move)
		--TCAPS.nb_move;
	tcaps_recalc_pos(e);
	if (TCAPS.nb_col == WIN_WIDTH - 1)
		xputs("cd");
	xputs("dc");
	--TCAPS.nb_read;
	xputs("ed");
}

void		tcaps_del_bkw(t_env *e)
{
	if (TCAPS.nb_move == TCAPS.nb_read)
		tcaps_del_bkw_end(e);
	else
	{
		if (!NB_READ && e->line)
			strfree(&e->line);
		xputs("le");
		--NB_READ;
		if (NB_MOVE)
			--NB_MOVE;
		tcaps_putstr(e, e->line);
	}
}
