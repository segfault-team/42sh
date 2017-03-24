#include "shell.h"

int	is_valid_arg(char **cmd, char *sh_name)
{
	int	i;
	int	j;

	i = 0;
	if (cmd[1] && cmd[2] && is_only_numbers(cmd[1]))
		return (history_error_with_id(cmd, sh_name, 1));
	return (1);
/*	while (cmd[++i])
	{
		if (cmd[i][0] != '-' && !is_number(cmd[i][0]))
			return (ft_error(sh_name, cmd[
	}
*/}
