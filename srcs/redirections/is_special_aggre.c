#include "shell.h"

int		is_special_aggre_in_line(t_env *e, int i)
{
	while (--i && e->line[i] && e->line[i] == '>')
		;
	if (i && e->line[i] != ' ')
		return (1);
	return (0);
}

int		is_invalid_spe_aggre(t_env *e, int i)
{
	int	k;
	int	len;

	if (!is_magic(e, i))
		return (0);
	len = (int)ft_strlen(e->magic[i].cmd);
	k = -1;
	while (++k && k < len && e->magic[i].cmd[k] != '>')
		;
	while (++k && k < len && e->magic[i].cmd[k] == '>')
		;
	if (k == len || e->magic[i].cmd[k] == ' ')
		return (1);
	return (0);
}

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
	if (j && e->magic[i].cmd[j + 1] && e->magic[i].cmd[j + 1] == '>'
		&& e->magic[i].cmd[j] == '>')
		return (1);
	return (0);
}
