#include "shell.h"

void	tcaps_ctrl_d(t_env *e)
{
	if (MULTI || NB_READ)
		tcaps_del_fwd(e);
	else
		ft_exit(e);
}

/*
**  INSTRUCTION FOR "Ctrl + a" KEYS || cmd: home
**
**  cr: return at the begining of the line
**  nd: move cursor once on the right
*/

void    tcaps_ctrl_home(t_env *e)
{
	int     i;
	int 	l;

	l = NB_READ;
	while (l--)
	{
		xputs("le");
		NB_MOVE = 0;
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
	while (NB_MOVE < NB_READ)
		move_right(e);
}
