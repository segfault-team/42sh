#include "shell.h"

/*
**  INSTRUCTION FOR ALL INSERTION
**		OF VISIBLE CHAR
**
**  im: start insert mode
**  ei: end insert mode
*/

void	inst_term_insert(t_env *e)
{
	char	*res;

	res = tgetstr("im", NULL);
	tputs(res, 1, dsh_putchar);
	tputs(&BUF[0], 1, dsh_putchar);
	res = tgetstr("ei", NULL);
	tputs(res, 1, dsh_putchar);
	++TCAPS.nb_move;
}
