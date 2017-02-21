#include "shell.h"

void	print_auto_completion(t_env *e, char *arg)
{
	int	i;

	i = ft_strlen(arg);
	ft_realloc_insert_str(e, arg);
	ft_printf("%s", arg);
	NB_READ += i;
	NB_MOVE += i;
}
