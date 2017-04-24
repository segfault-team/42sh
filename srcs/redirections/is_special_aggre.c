#include "shell.h"

int		is_special_aggre(t_env *e, int i)
{
	int	j;

	j = -1;
	if (i >= e->len_mag || !e->magic[i].cmd)
		return (0);
	while (e->magic[i].cmd[++j] && is_number(e->magic[i].cmd[j]))
		;
	if (!e->magic[i].cmd[j] || !e->magic[i].cmd[j + 1]
		|| e->magic[i].cmd[j] != '>')
		return (0);
	if (e->magic[i].cmd[j + 1] && e->magic[i].cmd[j + 1] == '>'
		&& e->magic[i].cmd[j] == '>')
		return (1);
	return (0);
}
