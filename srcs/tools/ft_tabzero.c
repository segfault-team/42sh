#include "shell.h"

void	ft_tabzero(char **dbl_tab, int len_tab)
{
	int	i;

	i = -1;
	while (++i <= len_tab)
		dbl_tab[i] = NULL;
}
