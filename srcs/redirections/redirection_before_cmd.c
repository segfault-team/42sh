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
		while (e->magic[RED_INDEX].cmd && !is_redir_pipe(e, RED_INDEX)
			   && RED_INDEX && !is_operator(e, RED_INDEX))
		{
			struct_find_red(e);
			if (is_input_redir(e, RED_INDEX))
			{
				ret = redir_input(e);
				pipe(FD.fd);
			}
		}
		return ((ret = dup2(FD.fd[1], STDOUT_FILENO)));
	}
	else if (is_heredoc(e, RED_INDEX))
		ret = redir_from_hdoc(e);
	else if (is_input_redir(e, RED_INDEX))
	{
		ret = redir_input(e);
		if (!is_last_cmd(e, RED_INDEX))
			pipe(FD.fd);
	}
	else if (is_heredoc(e, RED_INDEX))
		ret = redir_from_hdoc(e);
	if (ret == -1)
		return (-1);
	nxt_redir = is_next_redir(e, RED_INDEX);
	if (((is_redir_pipe(e, RED_INDEX) && nxt_redir != PIPE) ||
		!is_redir_pipe(e, RED_INDEX)) && !is_operator(e, RED_INDEX)
		&& RED_INDEX && nxt_redir != -1 && nxt_redir != OPERATOR)
	{
		struct_find_red(e);
		return (redirection_before_cmd(e));
	}
	return (1);
}
