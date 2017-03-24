#include "shell.h"

t_env	*env_access(t_env *e)
{
	static t_env	*pnt = NULL;

	if (e)
		pnt = e;
	return (pnt);
}
