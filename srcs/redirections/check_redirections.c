#include "shell.h"

int		is_redirection(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].type, "red"))
		return (1);
	return (0);
}

int		is_output_redir(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, ">") ||
		!ft_strcmp(e->magic[i].cmd, ">>"))
		return (1);
	return (0);
}

int		is_input_redir(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, "<"))
		return (1);
	return (0);
}

int		is_heredoc(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, "<<"))
		return (1);
	return (0);
}

int		is_aggregator(t_env *e, int i)
{
	if (ft_strstr(e->magic[i].cmd, "<&") ||
		ft_strstr(e->magic[i].cmd, ">&"))
		return (1);
	return (0);
}

int		is_redir_pipe(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, "|"))
		return (1);
	return (0);
}

int		is_input_file(t_env *e, int i)
{
	if (!e->magic[i].cmd ||
		ft_strcmp(e->magic[i].type, "input"))
		return (0);
	return (1);
}

int		is_redir_from_symbol(t_env *e, int i)
{
	if (is_output_redir(e, i) ||
		is_input_redir(e, i) ||
		is_aggregator(e, i) ||
		is_redir_pipe(e, i))
		return (1);
	return (0);
}

int		is_next_redir(t_env *e, int i)
{
	++i;
	while (e->magic[i].cmd && !is_redirection(e, i))
		++i;
	if (!e->magic[i].cmd)
		return (-1);
	if (ft_strstr(e->magic[i].cmd, ">&") != NULL ||
		ft_strstr(e->magic[i].cmd, "<&") != NULL)
		return (AGGREGATOR);
	else if (is_redir_pipe(e, i))
		return (PIPE);
	else if (is_output_redir(e, i))
		return (OUTPUT);
	else if (is_input_redir(e, i))
		return (INPUT);
	return (-1);
}

int		is_input_in_next_cmd(t_env *e, int i)
{
	++i;
	while (e->magic[i].cmd && !is_redir_pipe(e, i) && !is_input_redir(e, i))
		++i;
	if (is_input_redir(e, i))
		return (1);
	return (0);
}
