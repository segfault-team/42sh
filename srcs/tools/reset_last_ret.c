#include "shell.h"

void	reset_last_ret(t_env *e, int ret)
{
	strfree(&e->last_ret);
	e->last_ret = ft_itoa(ret);
}

void	reset_last_ret_builtin(t_env *e, int ret)
{
	if (ret < 0)
		ret = 1;
	else
		ret = 0;
	strfree(&e->last_ret);
	e->last_ret = ft_itoa(ret);
}
