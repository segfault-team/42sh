#include "shell.h"

char **delete_line_in_tab(char **ttab, int d)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(new = ft_tabnew(ft_tablen(ttab) - 1)))
		return (NULL);
	while (ttab[++i])
	{
		if (i != d)
			new[++j] = ft_strdup(ttab[i]);
	}
	new[++j] = NULL;
	return (new);
}
