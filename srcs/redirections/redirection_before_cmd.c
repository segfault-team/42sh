#include "shell.h"

int		redirection_before_cmd(t_env *e)
{
	int	ret;
	int	nxt_redir;

	ret = 0;
	if (is_aggregator(e, RED_INDEX))
		ret = redir_to_aggregator(e);
	else if (is_redir_pipe(e, RED_INDEX))
	{
		e->check_input = 1;
		return (dup2(FD.fd[1], STDOUT_FILENO));
	}
	else if (is_output_redir(e, RED_INDEX))
		dup2(FD.fd[1], STDOUT_FILENO);
	else if (e->hdoc && is_heredoc(e, RED_INDEX))
		ret = redir_from_hdoc(e);
	else if (is_input_redir(e, RED_INDEX))
	{
		ret = redir_input(e);
		e->check_input = 1;
	}
	if (ret == -1)
		return (-1);
	nxt_redir = is_next_redir(e, RED_INDEX);
	if (nxt_redir != PIPE && nxt_redir != -1 && nxt_redir != OPERATOR)
	{
		struct_find_red(e);
		return (redirection_before_cmd(e));
	}
	else if (nxt_redir == PIPE)
	{
		dup2(FD.fd[1], STDOUT_FILENO);
		struct_find_red(e);
	}
	return (1);
}
