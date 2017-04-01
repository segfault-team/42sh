#include "shell.h"

void		ft_exit(t_env *e)
{
	if (e->cmd && e->cmd[1])
	{
		if (!ft_strisdigit(e->cmd[1]))
		{
			e->exit = 255;
			ft_error("exit", e->cmd[1], "numeric argument required");
		}
		else
			e->exit = ft_atoi(e->cmd[1]);
	}
	else
		e->exit = 0;
	e->x = 0;
	if (tcaps_reset(e) && !e->raw)
		ft_error(SH_NAME, "cannot reset termios structure", NULL);
}
