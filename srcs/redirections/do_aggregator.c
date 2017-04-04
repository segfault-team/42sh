#include "shell.h"

void output_aggre(t_env *e, int fd_src, int fd_dst)
{
	if (fd_src != fd_dst)
	{
		if (!is_last_cmd(e, RED_INDEX))
		{
			if (fd_src != 1)
				dup2(FD.fd[1], fd_src);
			else
				dup2(STDOUT_FILENO, FD.fd[1]);
		}
		else
			dup2(fd_dst, fd_src);
	}
}

void close_aggre(t_env *e, int fd_src, int fd_dst)
{
	if (fd_src == 1 && !is_last_cmd(e, RED_INDEX) && !e->is_out_close)
	{
		++e->is_out_close;
		close(FD.fd[1]);
	}
	else
		close(fd_src);
}
