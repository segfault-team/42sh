#include "shell.h"

/*
**	INSTRUCTION FOR DELETE KEY
**
**		dm: start delete mode
**		le : move left
**		dc : delete char
**		ed: end delete mode
*/

void	inst_term_del(t_env *e)
{
	char *res;

	--TCAPS.nb_read;
	res = tgetstr("dm", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("le", NULL);
	tputs(res, 1, dsh_putchar);
	if (TCAPS.nb_move)
		--TCAPS.nb_move;
	res = tgetstr("dc", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("ed", NULL);
	tputs(res, 1, dsh_putchar);
	if (!TCAPS.nb_read && e->line)
	{
		free(e->line);
		e->line = NULL;
	}
}
