#include "shell.h"

static int	manage_check_red(t_env *e, int i)
{
/*	if (e->magic[i + 1].cmd && !is_aggregator(e, i)
		&& (is_input_redir(e, i + 1) || is_output_redir(e, i + 1)))
	{

		return (token_error(e, i + 1));
	}
*/	if (e->magic[i + 1].type
		&& (is_input_redir(e, i) || is_output_redir(e, i) || is_heredoc(e, i))
		&& (is_input_redir(e, i + 1) || is_output_redir(e, i + 1) || is_heredoc(e, i + 1)))
		return (token_error(e, i + 1));
	return (0);
}

int			check_magic_content(t_env *e, int i)
{
	if (!e->magic[i + 1].cmd && is_redirection(e, i)
		&& !is_redir_pipe(e, i) && is_aggregator(e, i + 1))
		return (ft_error(SH_NAME, "syntax error near unexpected token","'newline'"));
	if (is_redirection(e, i) && manage_check_red(e, i) == -1)
		return (-1);
	else if (e->magic[i + 1].cmd && !ft_strcmp(e->magic[i].cmd, ";")
			&& !ft_strstr(e->magic[i + 1].cmd, ";"))
		return (ft_error(SH_NAME, "syntax error near unexpected token \"%s\"",
						  e->magic[i + 1].cmd));
	return (0);
}
