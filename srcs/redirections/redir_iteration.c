#include "shell.h"

/*
**	FIND THE NEXT REDIRECTION IF THERE IS ONE
*/

void	struct_find_red(t_env *e)
{
	++(RED_INDEX);
	while (e->magic[RED_INDEX].cmd &&
			ft_strcmp(e->magic[RED_INDEX].type, "red"))
		++(RED_INDEX);
	if (!(e->magic[RED_INDEX].cmd))
		RED_INDEX = 0;
}

/*
**	CHECK SI red EST L'ACTUELLE REDIRECTION
*/

int		redir_check_red(t_env *e, char *red)
{
	if (e->magic[RED_INDEX].cmd && red &&
			!ft_strcmp(e->magic[RED_INDEX].cmd, red))
		return (1);
	return (0);
}

/*
**	CONTENUE DE L'ITERATION DE e->cat[i] (contient les cmds split par "red")
*/

int		redir_exec_open(int i, t_env *e)
{
	int		ret;

	ret = 0;
	if (!is_last_cmd(e, RED_INDEX) && )//ou si une redirection ver sfichier dedans)
		if (pipe(FD.fd) < 0)
			return (ft_error(SH_NAME, "Pipe failed.", NULL));
	struct_find_red(e);
	ret = ft_exec_cmd(e, e->cat[i]);
	FD.in = FD.fd[0];
	return (ret);
}
