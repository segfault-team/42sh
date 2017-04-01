#include "shell.h"

int		struct_len(t_env *e)
{
	int		len;

	len = -1;
	while (e->magic[++len].cmd)
		;
	return (len);
}
