/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:27:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/17 14:08:27 by lfabbro          ###   ########.fr       */
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

void	tcaps_del_fwd(t_env *e)
{
	char	*res;
	char	buf[3];

	ft_bzero(buf, 3);
	read(0, buf, 3);
	if (tcaps_check_key(buf, 126, 0, 0))
	{
		res = tgetstr("dm", NULL);
		tputs(res, 1, dsh_putchar);
		res = tgetstr("dc", NULL);
		tputs(res, 1, dsh_putchar);
		res = tgetstr("ed", NULL);
		tputs(res, 1, dsh_putchar);
		if (!TCAPS.nb_read && e->line)
		{
			free(e->line);
			e->line = NULL;
		}
		ft_realloc_delete_char(e, TCAPS.nb_move + 1);
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
