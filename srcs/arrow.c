#include "shell.h"

/*
**	INSTRUCTION FOR UP/DOWN
**		ARROW KEYS
**
**	cr: return at the begining of the line
**  cd: clear the line
*/

void	inst_term_history(t_env *e)
{
	char *res;

	res = tgetstr("cr", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("cd", NULL);
	tputs(res, 1, dsh_putchar);
	ft_putstr(e->prompt);
	if (check_key(BUF, 27, 91, 65))
		term_history_up(e);
	else
		term_history_down(e);
}

/*
**	INSTRUCTION FOR RIGHT
**		ARROW KEYS
**
**  nd: move cursor once on the right
*/

void	inst_term_right(t_env *e)
{
	char	*res;

	res = tgetstr("nd", NULL);
	tputs(res, 1, dsh_putchar);
	++TCAPS.nb_move;
}

/*
**	INSTRUCTION FOR LEFT
**		ARROW KEYS
**
**  le: move cursor once on the left
*/

void	inst_term_left(t_env *e)
{
	char	*res;

	res = tgetstr("le", NULL);
	tputs(res, 1, dsh_putchar);
	--TCAPS.nb_move;
}
