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

static void	ft_free_list_pid(t_env *e)
{
	void *ptr;

	e->actual_pid = e->pid_list;
	while (e->actual_pid)
	{
		ptr = e->actual_pid;
		e->actual_pid = e->actual_pid->next;
		ft_memdel(&ptr);
	}
	e->pid_list = NULL;
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
	int	status;
	int tmp;

	status = 0;
	if (!RED_INDEX || isRedirPipe(e, RED_INDEX))
	{
		FD.fd[1] = STDOUT_FILENO;
		ret = ft_exec_cmd(e, e->cat[i]);
	}
	else// if (isOutputRedir(e, RED_INDEX))
		redir_fill_output(e);
	{
		ret = ft_exec_cmd(e, e->cat[i]);
		dup2(FD.stdin, STDIN_FILENO);
		dup2(FD.stdout, STDOUT_FILENO);
		dup2(FD.stderr, STDERR_FILENO);
	}
	ret = 0;
	while (!ret)
	{
		ret = 42;
		e->actual_pid = e->pid_list;
		while (e->actual_pid)
		{
			tmp = waitpid(e->actual_pid->pid, &status, WNOHANG);
			if (!tmp)
				ret = tmp;
			e->actual_pid = e->actual_pid->next;
		}
		usleep(5);
	}
	if (tcsetattr(0, TCSADRAIN, &TCAPS.termos) == -1)
		ft_printf("GERRER ERREUR");
	ft_free_list_pid(e);
	singletonne(0);
	return (ret);
}
