#include "shell.h"

/*
**	FIND THE NEXT REDIRECTION IF THERE IS ONE
*/

void     struct_find_red(t_env *e)
{
	++(RED_INDEX);
	while (e->magic[RED_INDEX].cmd && ft_strcmp(e->magic[RED_INDEX].type, "red"))
		++(RED_INDEX);
	if (!(e->magic[RED_INDEX].cmd))
		RED_INDEX = 0;
}

/*
**	CHECK SI red EST L'ACTUELLE REDIRECTION
*/

int		redir_check_red(t_env *e, char *red)
{
	if (e->magic[RED_INDEX].cmd && red && !ft_strcmp(e->magic[RED_INDEX].cmd, red))
		return (1);
	return (0);
}

/*
**	CONTENUE DE L'ITERATION DE e->cat[i] (contient les cmds split par "red")
*/

int		redir_exec_open(int i, t_env *e)
{
	int	ret;
	int	cpy_red_index;

	cpy_red_index = RED_INDEX;
	ret = 0;
	struct_find_red(e);
	if (pipe(FD.fd) < 0)
		return (ft_error(SH_NAME, "Pipe failed.", NULL));
	ret = ft_exec_cmd(e, e->cat[i]);
	FD.in = FD.fd[0];
	return (ret);
}

/*
**	INSTRUCTION POUR LA DERNIERE CMD (OU LA SEULE) A EXECUTER
**	restauration des fd
**  '>' && '>>' 	== open
**	'|'				== exec
*/

int		redir_last_cmd(int i, t_env *e)
{
	int	ret;

	ret = 0;
	if (redir_check_red(e, "|") || !RED_INDEX)
	{
		FD.fd[1] = STDOUT_FILENO;
		ret = ft_exec_cmd(e, e->cat[i]);
	}
	else
	{
		if (redir_check_red(e, ">"))
			redir_fill_output(e);
		dup2(FD.stdin, STDIN_FILENO);
		dup2(FD.stdout, STDOUT_FILENO);
		dup2(FD.stderr, STDERR_FILENO);
	}
	return (ret);
}
