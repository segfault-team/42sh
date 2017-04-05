#include "shell.h"
int		history_delete(t_env *e, char **cmd, int i)
{
	int		len;
	char	**tmp;

	len = -1;
	if (!e->history)
		return (ft_error("history", cmd[i], "position out of range"));
	if (i == -1 || i > (int)ft_tablen(cmd))
		return (ft_error("history", "-d:", "option requires an argument"));
	if (!e->history || !is_only_numbers(cmd[i]) ||
		((len = ft_atoi(cmd[i])) > 2147483647) || len < 1  || !e->history[len])
		return (ft_error("history", cmd[i], "position out of range"));
	tmp = e->history;
	e->history = delete_line_in_tab(e->history, --len);
	ft_free_tab(tmp);
	return (1);
}
