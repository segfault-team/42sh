#include "shell.h"

int	is_valid_arg(char **cmd, char *sh_name)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '-' && !is_number(cmd[i][0]))
//			return (ft_error(sh_name, "
	}
}
