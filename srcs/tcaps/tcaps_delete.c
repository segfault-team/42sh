/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:27:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/20 19:27:58 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 **	DELETES KEYS INSTRUCTIONS
 **
 **		tcaps_del_bkw : BACKSPACE
 **		tcaps_del_fwd : DELETE
 **
 **		dm: start delete mode
 **		le : move left
 **		nd : move right
 **		dc : delete char
 **		ed: end delete mode
 **
 **
 **	LEGENDA
 ** 	nb_read		= strlen de line
 ** 	nb_move		= position curseur sur line
 ** 	ws.ws_col	= nombre de colones dans la fenetre
 ** 	nb_col		= emplacement du curseur sur UNE ligne par rapport a ws_col
 ** 	nb_line		= numero de la ligne
 */

int		more_than_a_line(t_env *e)
{
	unsigned short	len;

	len = (unsigned short)ft_strlen(e->line);
	if (len > TCAPS.ws.ws_row - 3)
		return (1);
	return (0);
}

void	tcaps_del_fwd(t_env *e)
{
	char	buf[3];

	ft_bzero(buf, 3);
	read(0, buf, 3);
	if (tcaps_check_key(buf, 126, 0, 0) && TCAPS.nb_move != TCAPS.nb_read)
	{
		if (!TCAPS.nb_read)
			strfree(&e->line);
		e->line = ft_realloc_delete_char(e, TCAPS.nb_move);
		if (more_than_a_line(e))
			tcaps_putstr(e, e->line);
		else
		{
			xputs("dm");
			xputs("dc");
			xputs("ed");
		}
		tcaps_recalc_pos(e);
		if (TCAPS.nb_read)
			--TCAPS.nb_read;
	}
}

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
		// Pourquoi si on a rien lu on efface line?
		if (!TCAPS.nb_read)
			strfree(&e->line);
		xputs("le");
		// nb_read peut etre < 0 ?
		--TCAPS.nb_read;
		if (TCAPS.nb_move)
			--TCAPS.nb_move;
		tcaps_putstr(e, e->line);
	}
}
