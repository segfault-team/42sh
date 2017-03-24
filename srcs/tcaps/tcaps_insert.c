#include "shell.h"

/*
**  INSTRUCTION FOR ALL INSERTION
**		OF VISIBLE CHAR
**
**  im: start insert mode
**  ei: end insert mode
*/

void	tcaps_insert(t_env *e)
{
	xputs(TGETSTR_IM);
	tputs(&BUF[0], 1, dsh_putchar);
	xputs(TGETSTR_EI);
	tcaps_recalc_pos(e);
}
