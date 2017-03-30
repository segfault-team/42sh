#include "shell.h"

#define ERROR		 	-1
#define INPUT_AGGRE     0
#define OUTPUT_AGGRE    1
#define ERROR_FILENUMBER -4242

static int	aggregator_error(int id, char *sh_name)
{
	if (id == 1)
		ft_printfd(STDERR_FILENO, "%s: bad file descriptor\n", sh_name);
	else if (id == ERROR_FILENUMBER)
		ft_printfd(STDERR_FILENO, "%s: file number expected\n", sh_name);
	else
		ft_printfd(STDERR_FILENO, "%s: redirection syntax error\n", sh_name);
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
	if (fd_dst == ERROR_FILENUMBER)
		return (aggregator_error(ERROR_FILENUMBER, SH_NAME));
	else if ((!isatty(fd_src) || !isatty(fd_dst)) && fd_dst != -42)
		return (aggregator_error(1, SH_NAME));
	ag_type = find_aggregator_type(e);
	if (fd_dst == ERROR || (fd_src == ERROR && ag_type == OUTPUT_AGGRE))
		return (aggregator_error(42, SH_NAME));
	if (ag_type == ERROR)
		return (-1);
	else if (fd_dst == -42)
	{
		close(fd_src);
		close(FD.fd[1]);
	}
	else if (ag_type == INPUT_AGGRE)
		dup2(fd_src, fd_dst);
	else
		output_aggre(e, fd_src, fd_dst);
	return (1);
}
