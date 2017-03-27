#include "shell.h"

#define ERROR		 	-1
#define INPUT_AGGRE     0
#define OUTPUT_AGGRE    1

static int	aggregator_error(int id)
{
	if (id == 1)
		dprintf(STDERR_FILENO, "sh: bad file descriptor\n");
	else
		dprintf(STDERR_FILENO, "sh: redirection syntax error\n");
	return (-1);
}

static void	output_aggre(t_env *e, int fd_src, int fd_dst)
{
	if (fd_src != fd_dst)
	{
		if (is_redir_pipe(e, RED_INDEX + 1))
			dup2(FD.fd[1], fd_src);
		else
			dup2(fd_dst, fd_src);
	}
}

int			redir_to_aggregator(t_env *e)
{
	int		fd_src;
	int		fd_dst;
	int		ag_type;

	fd_src = isolate_fd_source(e);
	fd_dst = isolate_fd_destination(e);
	if ((!isatty(fd_src) || !isatty(fd_dst)) && fd_dst != -42)
		return (aggregator_error(1));
	ag_type = find_aggregator_type(e);
	if (fd_dst == ERROR || (fd_src == ERROR && ag_type == OUTPUT_AGGRE))
		return (aggregator_error(42));
	if (ag_type == ERROR)
		return (-1);
	else if (fd_dst == -42)
		close(fd_src);
	else if (ag_type == INPUT_AGGRE)
		dup2(fd_src, fd_dst);
	else
		output_aggre(e, fd_src, fd_dst);
	struct_find_red(e);
	return (1);
}
