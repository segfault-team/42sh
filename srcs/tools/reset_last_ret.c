#include "shell.h"

void	reset_last_ret(t_env *e, int ret)
{
	strfree(&e->last_ret);
	e->last_ret = ft_itoa(ret);
}
