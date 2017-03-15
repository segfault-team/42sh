#include "shell.h"

int			ft_redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
		{
			if (close(oldfd) < 0)
				return (ft_error(SH_NAME, "Failed closing fd", NULL));
		}
		else
			return (ft_error(SH_NAME, "dup2 failed", NULL));
	}
	return (0);
}

int			ft_redirect_blt(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
			return (ft_error(SH_NAME, "dup2 failed", NULL));
	}
	return (0);
}

int			ft_redir_builtin(t_env *e)
{
	if (redir_check_red(e, "|") || redir_check_red(e, ">") || \
			redir_check_red(e, ">>"))
	{
		if (ft_redirect_blt(FD.in, STDIN_FILENO) ||
				ft_redirect_blt(FD.fd[1], STDOUT_FILENO))
			return (-1);
	}
	return (0);
}
