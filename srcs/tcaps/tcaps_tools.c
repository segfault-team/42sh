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
