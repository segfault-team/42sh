#include "shell.h"

int		redirection_before_cmd(t_env *e)
{
	int	ret;

	ret = 0;
	if (is_aggregator(e, RED_INDEX))
		ret = redir_to_aggregator(e);
	else if (redir_check_red(e, "|") || is_output_redir(e, RED_INDEX))
		ret = dup2(FD.fd[1], STDOUT_FILENO);
//	else if (is_input_redir(e, RED_INDEX))
//		ret = redir_input(e);
	if (ret == -1)
		return (-1);
	// TESTER EN PROFONDER POUR LES PIPES
	if (e->magic[RED_INDEX + 1].cmd && is_redirection(e, RED_INDEX + 1) &&
		!is_input_redir(e, RED_INDEX + 1))
	{
		++RED_INDEX;
		return (redirection_before_cmd(e));
	}
	return (1);
}
