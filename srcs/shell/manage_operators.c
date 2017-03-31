#include "shell.h"

int		manage_operators(t_env *e, int i, int ret)
{
	if (is_and(e, i) && ret == 1)
		return (0);
	else if (is_and(e, i) && ret == -1)
		return (1);
	else if (is_or(e, i) && ret == 1)
		return (1);
	else if (is_or(e, i) && ret == -1)
		return (0);
	return (0);
}
