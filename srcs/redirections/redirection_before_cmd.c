#include "shell.h"

static int		redirection_before_cmd_bis(t_env *e, int ret)
{
	int	nxt_redir;

	if (ret == -1)
		return (-1);
	nxt_redir = is_next_redir(e, RED_INDEX);
//	if (/*(is_redir_pipe(e, RED_INDEX) && nxt_redir != PIPE
//		  && nxt_redir != -1 && nxt_redir != OPERATOR) ||*/
//		(!is_redir_pipe(e, RED_INDEX)
	if (nxt_redir != -1 && nxt_redir != OPERATOR)
	{
		struct_find_red(e);
		return (redirection_before_cmd(e));
	}
	return (1);
}

int				redirection_before_cmd(t_env *e)
{
	int		ret;

	ret = 0;
	if (is_aggregator(e, RED_INDEX) && !is_output_after(e, RED_INDEX))
		ret = redir_to_aggregator(e);
	else if (is_redir_pipe(e, RED_INDEX) && e->is_valid_pipe)
	{
		e->check_input = 1;
		if (e->is_out_close)
			return (close(STDOUT_FILENO));
		return (dup2(FD.fd[1], STDOUT_FILENO));
	}
	else if (is_output_redir(e, RED_INDEX))
		dup2(FD.fd[1], STDOUT_FILENO);
	else if (e->hdoc && is_heredoc(e, RED_INDEX))
	{
		ret = redir_from_hdoc(e);
	}
	else if (is_input_redir(e, RED_INDEX))
	{
		ret = redir_input(e);
		e->check_input = 1;
	}
	return (redirection_before_cmd_bis(e, ret));
}
