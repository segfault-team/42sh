#include "shell.h"
/*
static int	litlle_itoa(t_env *e, int curr, t_pos *p, char **cmd)
{
	while (e->cmd[curr][++(p->j)])
	{
		if (!is_number(e->cmd[curr][(p->j)]))
			return (history_delete_error(SH_NAME, cmd));
		p->i = p->i * 10 + e->cmd[curr][p->j] - '0';
	}
	--(p->i);
	return (0);
}

int			history_delete(t_env *e, char **cmd, int curr)
{
	t_pos	p;
	char	**tmp;

	p.i = (e->cmd[curr][2]) ? 0 : -1;
	p.j = 1;
	if (!p.i && litlle_itoa(e, curr, &p, cmd) == -1)
		return (-1);
	else if (!e->cmd[curr + 1])
		return (history_delete_error(SH_NAME, cmd));
	else
	{
		if (!is_only_numbers(cmd[curr + 1]) && p.i == -1)
			return (history_delete_error(SH_NAME, cmd));
		p.i = ft_atoi(cmd[curr + 1]) - 1;
	}
	if (p.i < 0 || !e->history[p.i])
		return (history_delete_error(SH_NAME, cmd));
	tmp = e->history;
	e->history = delete_line_in_tab(e->history, p.i);
	ft_free_tab(tmp);
	return (1);
}
*/

int		history_delete(t_env *e, char **cmd, int i)
{
	int		len;
	char	**tmp;

	len = -1;
	if (i == -1 || i > (int)ft_tablen(e->history) - 1 || !e->history[i])
		return (ft_error("history", "-d:", "option requires an argument"));
	if (!is_only_numbers(cmd[i]) || ((len = ft_atoi(cmd[i])) > 2147483647)
		|| len < 1  || !e->history[len])
		return (ft_error("history", cmd[i], "position out of range"));
	tmp = e->history;
	e->history = delete_line_in_tab(e->history, len);
	ft_free_tab(tmp);
	return (1);
}
