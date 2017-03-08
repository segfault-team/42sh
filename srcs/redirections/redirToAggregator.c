#include "shell.h"

#define ERROR		 	-420
#define INPUT_AGGRE     0
#define OUTPUT_AGGRE    1

void		outputAggre(t_env *e, int fd_src, int fd_dst)
{
	if (isRedirPipe(e, RED_INDEX + 1))
		dup2(FD.fd[1], fd_src);
	else
		dup2(fd_dst, fd_src);
}

int			redirToAggregator(t_env *e)
{
	int	fd_src;
	int	fd_dst;
	int	aggregatorType;

	fd_src = isolateFdSource(e);
	fd_dst = isolateFdDestination(e);
	if (fcntl(fd_src, F_GETFD) || fcntl(fd_dst, F_GETFD))
		return (dprintf(STDERR_FILENO, "sh:bad file descriptor\n"));
	aggregatorType = findAggregatorType(e);
//	ft_printf("s:%d | d:%d | t:%d\n", fd_src, fd_dst, aggregatorType);
	if (fd_dst == ERROR ||
		(fd_src == ERROR && aggregatorType == OUTPUT_AGGRE))
		return (dprintf(STDERR_FILENO, "sh: syntax error in your aggregator\n"));
//NEED TO MANAGE HERE WITH THE FD.in FD.fd[0] FD.fd[1]
	if (aggregatorType == ERROR)
		return (ERROR);
	else if (aggregatorType == INPUT_AGGRE)
		dup2(fd_dst, STDIN_FILENO);
	else
		outputAggre(e, fd_src, fd_dst);
//		if (e->magic[RED_INDEX + 1].cmd && isRedirPipe(e, RED_INDEX + 1))
//			dup2(FD.fd[1], fd_src);
//		else
//			dup2(FD.fd[1], fd_src);
	struct_find_red(e);
	return (1);
}
