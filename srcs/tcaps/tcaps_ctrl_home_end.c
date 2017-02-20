#include "shell.h"

/*
**  INSTRUCTION FOR "Ctrl + a" KEYS || cmd: home
**
**  cr: return at the begining of the line
**  nd: move cursor once on the right
*/

void    tcaps_ctrl_home(t_env *e)
{
	int     i;
	int l;

	l = TCAPS.nb_read;
	while (l--)
	{
		xputs("le");
		TCAPS.nb_move = 0;
	}
	xputs("cr");
	i = ft_strlen(e->prompt);
	while (i--)
		xputs("nd");
	tcaps_recalc_pos(e);
}

/*
**  INSTRUCTION FOR "Ctrl + e" KEYS || cmd: end
**
**  cr: return at the begining of the line
**  nd: move cursor once on the right
*/

void    tcaps_ctrl_end(t_env *e)
{
	tcaps_recalc_pos(e);
	while (TCAPS.nb_move < TCAPS.nb_read)
		move_right(e);
}
