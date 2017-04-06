#include "shell.h"

int		is_redir_pipe(t_env *e, int i)
{
	if (i >= (int)e->len_mag)
		return (0);
	if (!ft_strcmp(e->magic[i].cmd, "|"))
		return (1);
	return (0);
}

int		is_input_file(t_env *e, int i)
{
	if (i >= (int)e->len_mag)
		return (0);
	if (!e->magic[i].cmd || ft_strcmp(e->magic[i].type, "input"))
		return (0);
	return (1);
}

int		is_redir_from_symbol(t_env *e, int i)
{
	if (i >= (int)e->len_mag)
		return (0);
	if (is_output_redir(e, i) ||
		is_input_redir(e, i) ||
		is_aggregator(e, i) ||
		is_redir_pipe(e, i))
		return (1);
	return (0);
}

int		is_next_redir(t_env *e, int i)
{
	if (i >= (int)e->len_mag || !e->magic[i].cmd)
		return (-1);
	++i;
	if (i >= (int)e->len_mag)
		return (-1);
	while (e->magic[i].cmd && !red_strstr(e->magic[i].cmd)
			&& !is_operator(e, i))
		++i;
	if (!e->magic[i].cmd)
		return (-1);
	if (ft_strstr(e->magic[i].cmd, ">&") != NULL
		|| ft_strstr(e->magic[i].cmd, "<&") != NULL)
		return (AGGREGATOR);
	else if (is_redir_pipe(e, i))
		return (PIPE);
	else if (is_output_redir(e, i))
		return (OUTPUT);
	else if (is_input_redir(e, i))
		return (INPUT);
	else if (is_operator(e, i))
		return (OPERATOR);
	else if (is_heredoc(e, i))
		return (HEREDOC);
	return (-1);
}

int		is_input_in_next_cmd(t_env *e, int i)
{
	if (!i)
		return (0);
	if (i >= (int)e->len_mag)
		return (0);
	++i;
	while (e->magic[i].cmd && !is_redir_pipe(e, i) && !is_input_redir(e, i) \
			&& !is_operator(e, i))
		++i;
	if (is_input_redir(e, i))
		return (1);
	return (0);
}
