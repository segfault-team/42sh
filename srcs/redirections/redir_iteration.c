#include "shell.h"

/*
**	FIND THE NEXT REDIRECTION IF THERE IS ONE
*/

static void     struct_find_red(t_env *e)
{
	++(e->i_mag);
	while (e->magic[e->i_mag].cmd && ft_strcmp(e->magic[e->i_mag].type, "red"))
	{
		++(e->i_mag);
	}
	if (!(e->magic[e->i_mag].cmd))
		e->i_mag = 0;
}

/*
**	CHECK SI red EST L'ACTUELLE REDIRECTION
*/

int		redir_check_red(t_env *e, char *red)
{
	if (e->i_mag && e->magic[e->i_mag].cmd && \
			red && !ft_strcmp(e->magic[e->i_mag].cmd, red))
		return (1);
	return (0);
}

/*
**	CONTENUE DE L'ITERATION DE e->cat[i] (contient les cmds split par "red")
**	REDIRECT EM FONCTION DU TYPE DE REDIRECTION
**	'>' && '>>' 	== open
**	'|'				== exec
*/

int		redir_exec_open(int i, t_env *e)
{
	int	ret;

	ret = 0;
	struct_find_red(e);
	if (pipe(FD.fd) < 0)
		return (ft_error(SH_NAME, "Pipe failed.", NULL));
	if (redir_check_red(e, ">"))
	{
		if (!FD.last_red && (FD.fd[1] = open(e->magic[e->i_mag + 1].cmd, ONE_RED_FLAGS, OPENFLAGS)) == -1)
			ft_printf("MANAGE ERROR");
		dup2(FD.fd[1], STDOUT_FILENO);
		dup2(FD.in, STDIN_FILENO);
	}
	ret = ft_exec_cmd(e, e->cat[i]);
	FD.in = FD.fd[0];
	return (ret);
}

/*
**	INSTRUCTION POUR LA DERNIERE CMD (OU LA SEULE) A EXECUTER
**	restauration des fd
*/

int		redir_last_cmd(int i, t_env *e)
{
	int	ret;

	ret = 0;
	if (redir_check_red(e, "|") || !e->i_mag)
	{
		FD.fd[1] = STDOUT_FILENO;
		ret = ft_exec_cmd(e, e->cat[i]);
	}
	else
	{
		dup2(FD.stdin, STDIN_FILENO);
		dup2(FD.stdout, STDOUT_FILENO);
		dup2(FD.stderr, STDERR_FILENO);
	}
	return (ret);
}
