#include "shell.h"

int	is_last_cmd(t_env *e, int i)
{
	while (i < e->len_mag && e->magic[i].cmd
		   && !is_redir_pipe(e, i)
		   && !is_operator(e, i))
		++i;
	if (i == e->len_mag && !e->magic[i].cmd)
		return (1);
	return (0);
}
