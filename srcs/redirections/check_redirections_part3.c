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
	if (e->magic[i].type && !ft_strcmp(e->magic[i].type, "operator"))
		return (1);
	return (0);
}

int		is_and(t_env *e, int i)
{
	if (e->magic[i].cmd && !ft_strcmp(e->magic[i].cmd, "&&"))
		return (1);
	return (0);
}

int		is_or(t_env *e, int i)
{
	if (e->magic[i].cmd && !ft_strcmp(e->magic[i].cmd, "||"))
		return (1);
	return (0);
}

int		find_nxt_operator(t_env *e)
{
	int	len;

	len = 1;
	if (RED_INDEX >= e->len_mag || !e->magic[RED_INDEX].cmd)
		return (0);
	while (e->magic[++RED_INDEX].cmd && !is_operator(e, RED_INDEX))
		if (is_redir_pipe(e, RED_INDEX))
			++len;
	return (len);
}
