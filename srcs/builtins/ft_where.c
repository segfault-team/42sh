/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_where.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 18:58:17 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/20 13:03:33 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_isbuiltin(char *cmd)
{
	if (ft_strequ(cmd, "exit"))
		return (1);
	else if (ft_strequ(cmd, "env"))
		return (1);
	else if (ft_strequ(cmd, "setenv"))
		return (1);
	else if (ft_strequ(cmd, "unsetenv"))
		return (1);
	else if (ft_strequ(cmd, "cd"))
		return (1);
	else if (ft_strequ(cmd, "echo"))
		return (1);
	else if (ft_strequ(cmd, "where"))
		return (1);
	else if (ft_strequ(cmd, "history"))
		return (1);
	return (0);
}

int			ft_where(t_env *e, char **cmd)
{
	int		i;
	int		ret;
	char	**paths;
	char	*path;

	i = 0;
	ret = 1;
	paths = ft_find_paths(e->env);
	e->cmd_len = ft_tablen(cmd);
	while (++i < (int)e->cmd_len)
	{
		if (ft_isbuiltin(cmd[i]) && ft_printf("%s is a shell built-in.", \
					cmd[i]))
			ret = 0;
		if ((path = ft_find_exec(paths, cmd[i])))
		{
			ret = 0;
			ft_putendl(path);
			strfree(&path);
		}
	}
	e->cmd_len = ft_tablen(e->cmd);
	ft_free_tab(paths);
	return (ret);
}
