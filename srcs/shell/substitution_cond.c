#include "shell.h"

void	substitution_cond(char **str, int *i, char *tmp)
{
	tmp = ft_strdup((*str));
	do_substitution(str, i, USERS_DIR, 0);
	if (access(&(*str)[*i], F_OK) == -1)
	{
		ft_strdel(str);
		*str = tmp;
	}
}
