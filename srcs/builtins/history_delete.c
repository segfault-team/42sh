/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:28:57 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:28:57 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*isolate_arg(char **cmd, int i)
{
	int		j;
	char	*new;

	if (i < 1 || !cmd || !cmd[i])
		return (NULL);
	j = -1;
	while (cmd[i][++j] && cmd[i][j] != 'd')
		;
	if (!cmd[i][++j] && cmd[i + 1])
		return (cmd[i + 1]);
	else if (!cmd[i][j] && !cmd[i + 1])
		return (NULL);
	if (!(new = ft_strsub(cmd[i], j, (int)ft_strlen(cmd[i]) - j)))
		return (NULL);
	return (new);
}

int			history_delete(t_env *e, char **cmd, int i)
{
	int		len;
	char	**tmp;
	char	*arg;

	len = -1;
	if (!e->history)
		return (ft_error("history", cmd[i], "position out of range"));
	arg = isolate_arg(cmd, i - 1);
	if (arg == NULL || i > (int)ft_tablen(cmd))
	{
		strfree(&arg);
		return (ft_error("history", "-d", "option requires an argument"));
	}
	if (!e->history || !is_only_numbers(arg)
		|| ((len = ft_atoi(arg)) > 2147483647)
		|| len < 1 || len > (int)ft_tablen(e->history) || !e->history[len])
	{
		strfree(&arg);
		return (ft_error("history", cmd[i], "position out of range"));
	}
	tmp = e->history;
	e->history = delete_line_in_tab(e->history, --len);
	ft_free_tab(tmp);
	return (1);
}
