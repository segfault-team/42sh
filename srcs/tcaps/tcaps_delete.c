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

void		tcaps_del_fwd(t_env *e)
{
	char	buf[3];

	ft_bzero(buf, 3);
	if (BUF[0] != CTRL_D)
		read(0, buf, 3);
	else
		buf[0] = 126;
	if (tcaps_check_key(buf, 126, 0, 0) && NB_READ && NB_MOVE != NB_READ)
	{
		xputs(TGETSTR_DM);
		xputs(TGETSTR_DC);
		xputs(TGETSTR_ED);
		if (!(NB_READ - 1))
			strfree(&e->line);
		e->line = ft_realloc_delete_char(e, NB_MOVE);
		if (!NB_READ && e->line)
			strfree(&e->line);
		--NB_READ;
		xputs(TGETSTR_VI);
		tcaps_putstr(e, e->line);
		xputs(TGETSTR_VE);
	}
}

static void	tcaps_del_bkw_end(t_env *e)
{
	xputs(TGETSTR_DM);
	xputs(TGETSTR_LE);
	if (NB_MOVE)
		--NB_MOVE;
	tcaps_recalc_pos(e);
	if (TCAPS.nb_col == WIN_WIDTH - 1)
		xputs(TGETSTR_CD);
	xputs(TGETSTR_DC);
	--NB_READ;
	xputs(TGETSTR_ED);
}

void		tcaps_del_bkw(t_env *e)
{
	if (NB_MOVE == NB_READ)
		tcaps_del_bkw_end(e);
	else
	{
	// Pourquoi si on a rien lu on efface line?
		if (!NB_READ)
			strfree(&e->line);
		xputs(TGETSTR_LE);
		--NB_READ;
		if (NB_MOVE)
			--NB_MOVE;
		xputs(TGETSTR_VI);
		tcaps_putstr(e, e->line);
		xputs(TGETSTR_VE);
	}
}
