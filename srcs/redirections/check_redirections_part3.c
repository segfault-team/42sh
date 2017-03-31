#include "shell.h"

int		is_put_after(t_env *e)
{
	int	red;

	red = RED_INDEX;
	while (e->magic[++red].cmd && !is_redir_pipe(e, red))
		if (!ft_strcmp(e->magic[red].type, "output")
			|| !ft_strcmp(e->magic[red].type, "input"))
			return (1);
	return (0);
}

int		is_operator(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].type, "operator"))
		return (1);
	return (0);
}

int		is_and(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, "&&"))
		return (1);
	return (0);
}

int		is_or(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, "||"))
		return (1);
	return (0);
}
