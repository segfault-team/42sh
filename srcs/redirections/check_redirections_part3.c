#include "shell.h"

int	is_put_after(t_env *e)
{
	int	red;

	red = RED_INDEX;
	while (e->magic[++red].cmd && !is_redir_pipe(e, red))
		if (!ft_strcmp(e->magic[red].type, "output")
			|| !ft_strcmp(e->magic[red].type, "input"))
			return (1);
	return (0);
}
