#include "shell.h"

static int	is_redir_sign(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}

int			ft_check_input(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, "<") ||
		!ft_strcmp("input", e->magic[i].type))
		return (1);
	return (0);
}

int			ft_check_output(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, ">") ||
		!ft_strcmp(e->magic[i].cmd, ">>") ||
		!ft_strcmp(e->magic[i].cmd, "|") ||
		!ft_strcmp("output", e->magic[i].type))
		return (1);
	return (0);
}

int			ft_check_heredoc(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, "<<") &&
		ft_strcmp("heredoc", e->magic[i].type))
		return (1);
	return (0);
}

/*
**  CHECK IF A REDIRECTION IS IN 'str'
*/

int			red_strstr(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (is_redir_sign(str[i]))
			return (1);
	return (0);
}

/*
**  CHECK IF CURRENT e->magic[i].cmd IS NOT A REDIRECTION
**  OR A FILE FOR REDIRECTION
*/

int			struct_check_cmd(int i, t_env *e)
{
	if (i > 0 && is_redir_pipe(e, i - 1))
		return (1);
//	else if (i > 0 && !is_aggregator(e, i - 1) && !is_redirection(e, i))
//		return (1);
//  else if (OPERATOR LOGIQUE) return (1);
	else if (i == 0 && !red_strstr(e->magic[i].cmd))
		return (1);
	return (0);
}
