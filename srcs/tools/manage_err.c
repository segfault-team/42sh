#include "shell.h"

void	set_error(t_env *e, int errcode, char *err_msg)
{
	ERRCODE = errcode;
	ERRMSG = ft_strdup(err_msg);
}

void	free_error(t_env *e)
{
	ERRCODE = 0;
	strfree(&ERRMSG);
}

int		manage_err(t_env *e)
{
	if (ERRCODE == CMD_NF)
		return (ft_error(ERRMSG, "Command not found.", NULL));
	else if (ERRCODE == NSFOD)
		return (ft_error(ERRMSG, "No such file or directory.", NULL));
	else if (ERRCODE == PERM_DENIED)
		return (ft_error(ERRMSG, "permission denied.", NULL));
	else if (ERRCODE == DIRCLOSE_FAIL)
		return (ft_error(ERRMSG, "Failed closing directory", NULL));
	return (1);
}
