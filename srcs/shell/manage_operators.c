#include "shell.h"

static int	find_next_op(t_env *e, int i)
{
	while (i < (int)e->len_mag && e->magic[i].type && !is_operator(e, i))
		++i;
	if (i >= (int)e->len_mag || !e->magic[i].type)
		return (0);
	return (i);
}

int			manage_operators(t_env *e, int i, int ret)
{
	static	int		next_op = 0;

	if (!i)
		next_op = 0;
	if (!(next_op = find_next_op(e, next_op)))
		return (0);
	e->check_input = 0;
	if (is_and(e, next_op) && ret == 1)
		return (0);
	else if (is_and(e, next_op) && ret == -1)
		return (find_nxt_operator(e));
	else if (is_or(e, next_op) && ret == 1)
		return (find_nxt_operator(e));
	else if (is_or(e, next_op) && ret == -1)
	{
		close(FD.in);
		dup2(STDIN_FILENO, FD.in);
		return (0);
	}
	return (0);
}
