#include "shell.h"

void	ft_remove_tab(char ***pas_tab, int index)
{
	char	**ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(ret = ft_tabnew(ft_tablen(*pas_tab))))
		return ;
	while (*pas_tab[++i])
	{
		if (i == index)
			++i;
		else
			ret[++j] = ft_strdup(*pas_tab[i]);
	}
	ret[j] = NULL;
	ft_free_tab(*pas_tab);
	*pas_tab = ret;
}
