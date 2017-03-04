#include "shell.h"

#define ERROR		 	-420
#define INPUT_AGGRE     0
#define OUTPUT_AGGRE    1

static void	outputAggre(t_env *e, int fd_src, int fd_dst)
{
	if (fd_src == 2 && fd_dst == 1)
	{
		if (isRedirPipe(e, RED_INDEX + 1))
			ft_redirect(FD.fd[1], STDERR_FILENO);
		else
			ft_redirect(STDERR_FILENO, STDOUT_FILENO);
	}
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
	if (!isatty(fd_src) || !isatty(fd_dst))
		return (ft_error(SH_NAME, "bad file descriptor", NULL));
	aggregatorType = findAggregatorType(e);
//	ft_printf("s:%d | d:%d | t:%d\n", fd_src, fd_dst, aggregatorType);
	if (fd_dst == ERROR ||
		(fd_src == ERROR && aggregatorType == OUTPUT_AGGRE))
		return (ft_error(SH_NAME, "syntax error in your aggregator", NULL));
	if (aggregatorType == ERROR)
		return (ERROR);
	else if (aggregatorType == INPUT_AGGRE)
		dup2(fd_dst, STDIN_FILENO);
	else
		outputAggre(e, fd_src, fd_dst);
	struct_find_red(e);
	return (1);
}
