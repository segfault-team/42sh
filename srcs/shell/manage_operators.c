#include "shell.h"

static int	find_next_op(t_env *e, int i)
{
	static	int		next_op = 0;

	if (!i)
		next_op = 0;
	while (next_op < (int)e->len_mag && e->magic[next_op].type &&
			!ft_strcmp(e->magic[next_op].type, "cmd"))
		++next_op;
	++next_op;
	return (next_op - 1);
}

int			manage_operators(t_env *e, int i, int ret)
{
	int	op;

	op = find_next_op(e, i);
	if (op >= (int)e->len_mag || !e->magic[op].type ||
			ft_strcmp(e->magic[op].type, "operator"))
		return (0);
	e->check_input = 0;
	ret = ft_waitsons(e);
	RED_INDEX = op;
	if (is_and(e, op) && ret == 1)
		return (0);
	if (is_and(e, op) && ret == -1)
		return (find_nxt_operator(e));
	if (is_or(e, op) && ret == 1)
		return (find_nxt_operator(e));
	if (is_or(e, op) && ret == -1)
	{
		close(FD.in);
		dup2(STDIN_FILENO, FD.in);
		return (0);
	}
	return (0);
}
