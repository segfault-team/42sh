#include "shell.h"

int		redirection_before_cmd(t_env *e)
{
	int	ret;
	int	nxt_redir;

	ret = 0;
	if (is_aggregator(e, RED_INDEX))
		ret = redir_to_aggregator(e);
	else if (redir_check_red(e, "|") || is_output_redir(e, RED_INDEX))
	{
		while (e->magic[RED_INDEX].cmd && !is_redir_pipe(e, RED_INDEX) && RED_INDEX)
		{
//			ft_printfd(2, "BOID\n");
			struct_find_red(e);
		}
//		ft_printfd(2, "[%d]: %s\n", RED_INDEX, e->magic[RED_INDEX].cmd);
		return ((ret = dup2(FD.fd[1], STDOUT_FILENO)));
	}
	else if (is_heredoc(e, RED_INDEX))
		ret = redir_from_hdoc(e);
	if (ret == -1)
		return (-1);
//	if (e->magic[RED_INDEX + 1].cmd && is_redirection(e, RED_INDEX + 1) &&
//		!is_input_redir(e, RED_INDEX + 1) && !is_aggregator(e, RED_INDEX + 1))
//	if (!is_redir_pipe(e, RED_INDEX) && is_next_redir(e, RED_INDEX) != PIPE && RED_INDEX)
	nxt_redir = is_next_redir(e, RED_INDEX);
	if (((is_redir_pipe(e, RED_INDEX) && nxt_redir != PIPE) ||
		!is_redir_pipe(e, RED_INDEX)) && RED_INDEX)
	{
//		++RED_NDEX;
		struct_find_red(e);
		return (redirection_before_cmd(e));
	}
	return (1);
}
