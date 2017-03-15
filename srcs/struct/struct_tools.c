#include "shell.h"

int isMagic(t_env *e, int i)
{
	if (e->magic[i].cmd)
		return (1);
	return (0);
}

int	struct_len(t_magic *magic)
{
	int	len;

	len = 0;
	if (magic)
		while (magic[len].cmd)
			++len;
	return (len);
}

void	magic_free(t_env *e)
{
	int	i;

	i = -1;
	if (e->magic)
	{
		while (e->magic[++i].cmd)
		{
			if (e->magic[i].cmd)
			{
				free(e->magic[i].cmd);
				e->magic[i].cmd = NULL;
			}
			if (e->magic[i].type)
			{
				free(e->magic[i].type);
				e->magic[i].type = NULL;
			}
		}
		free(e->magic);
		e->magic = NULL;
	}
}
