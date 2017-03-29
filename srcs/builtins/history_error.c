#include "shell.h"

int	history_delete_error(char *sh_name, char **cmd)
{
	if (cmd[1][2])
		ft_printfd(2, "%s history: %s: history position out of range\n",
				sh_name, &cmd[1][2]);
	else if (cmd[2])
		ft_printfd(2, "%s history: %s: history position out of range\n",
				sh_name, cmd[2]);
	else
	{
		ft_printfd(2, "%s history -d: option requiere argument\n", sh_name);
		print_history_help();
	}
	return (-1);
}

int	history_error_with_id(char **cmd, char *sh_name, int id)
{
	if (id == 1)
		ft_printfd(2, "%s: history: too many arguments\n");
	else if (id == 2)
		ft_printfd(2, "%s: history: %s: too many arguments\n", sh_name, cmd[1]);
	return (0);
}
