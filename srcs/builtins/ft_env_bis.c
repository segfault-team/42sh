#include "shell.h"

int		ft_env_error(char *cmd)
{
	ft_printfd(2, "env: illegal option --%c\n", cmd[1]);
	ft_printfd(2, "usage: env [-i name1=val1 ...] [-u name]\n");
	return (-1);
}

int		ft_env_opt_u_error(char *cmd)
{
	if (!cmd)
	{
		ft_printfd(2, "env: option requires an argument -- u\n");
		ft_printfd(2, "usage: env [-i] [-u name]\n");
		ft_printfd(2, "           [name=value] [utility [argument ...]]\n");
	}
	else if (cmd)
		ft_printfd(2, "env: unsetenv %s: invalid argument", cmd);
	return (-1);
}
