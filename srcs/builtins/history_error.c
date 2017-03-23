#include "shell.h"

int	history_delete_error(char *sh_name, char **cmd)
{
	if (cmd[1][2])
		ft_printf("%s history: %s: history position out of range\n", sh_name, &cmd[1][2]);
	else if (cmd[2])
		ft_printf("%s history: %s: history position out of range\n", sh_name, cmd[2]);
	else
	{
		ft_printf("%s history -d: option requiere argument\n", sh_name);
		print_history_help();
	}
	return (-1);
}
