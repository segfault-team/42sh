#include "shell.h"

void	ft_create_file(t_env *e)
{
	int		i;
	int		fd;

	i = -1;
	fd = 0;
	while (e->magic[++i].type)
	{
		if (!ft_strcmp(e->magic[i].type, "output"))
		{
			if (i && !ft_strcmp(e->magic[i - 1].cmd, ">"))
				fd = open(e->magic[i].cmd, O_CREAT | O_TRUNC, OFLAGS);
			else
				fd = open(e->magic[i].cmd, O_CREAT , OFLAGS);
			ft_close(fd);
		}
	}
}
