/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_where.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 18:58:17 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/07 00:08:53 by lfabbro          ###   ########.fr       */
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
	return (0);
}

int			ft_where(t_env *e)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	paths = ft_find_paths(e->env);
	while (++i < (int)e->cmd_len)
	{
		if (ft_isbuiltin(e->cmd[i]))
			ft_error(e->cmd[i], "is a shell built-in", NULL);
		if ((path = ft_find_exec(paths, e->cmd[i])))
		{
			ft_putendl(path);
			free(path);
		}
	}
	ft_free_tab(paths);
	return (0);
}
