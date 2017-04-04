#include "shell.h"

int		dsh_putchar(int c)
{
	return (ft_putchar(c));
}

void	xputs(char *tcaps)
{
	if (tcaps)
		ft_putstr(tcaps);
}

void	move_right(t_env *e)
{
	if (TCAPS.nb_col == (WIN_WIDTH - 1))
	{
		xputs(TGETSTR_DW);
		xputs(TGETSTR_CR);
	}
	else
		xputs(TGETSTR_ND);
	++TCAPS.nb_move;
	tcaps_recalc_pos(e);
}

int		tcaps_is_delete_key(t_env *e)
{
	if (e->line && e->buf[0] == 127 && NB_MOVE > 0)
		return (1);
	return (0);
}
