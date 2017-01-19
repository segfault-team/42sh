/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 18:55:15 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/15 20:48:53 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**ft_parse_cmd(t_env *e)
{
	char	**cmds;
	char	*trline;

	trline = ft_strxtrim_quote(e->line, '\t');
	cmds = ft_strsplit(trline, ';');
	free(trline);
	return (cmds);
}

static int		ft_exec_builtin(t_env *e)
{
	char	ret;

	ret = 0;
	if (ft_strequ(e->cmd[0], "exit") && ++ret)
		ft_exit(e);
	else if (ft_strequ(e->cmd[0], "env") && ++ret)
		ft_env(e);
	else if (ft_strequ(e->cmd[0], "setenv") && ++ret)
		ft_setenv_blt(e);
	else if (ft_strequ(e->cmd[0], "unsetenv") && ++ret)
		ft_unsetenv_blt(e);
	else if (ft_strequ(e->cmd[0], "cd") && ++ret)
		ft_chdir(e);
	else if (ft_strequ(e->cmd[0], "echo") && ++ret)
		ft_echo(e);
	else if (ft_strequ(e->cmd[0], "where") && ++ret)
		ft_where(e);
	return (ret);
}

int				ft_exec_cmd(t_env *e, char **cmds, int i)
{
	int		ret;

	ret = 0;
	e->cmd = ft_strsplit_quote(cmds[i], ' ');
	e->cmd_len = ft_tablen(e->cmd);
	if (e->cmd_len)
	{
		if ((ret = ft_exec_builtin(e)))
			;
		else
			ret = ft_exec(e->cmd, e->env);
	}
	ft_free_tab(e->cmd);
	return (ret);
}

int				ft_parse_line(t_env *e)
{
	int		i;
	int		ret;
	char	**cmds;

	i = -1;
	ret = 0;
	if ((cmds = ft_parse_cmd(e)) != NULL)
	{
		while (cmds[++i])
		{
			if (ft_matchquotes(cmds[i]) == 0)
			{
				ret = ft_exec_cmd(e, cmds, i);
			}
			else
				ft_error(NULL, "Unmatched quote", NULL);
		}
	}
	ft_free_tab(cmds);
	return (ret);
}
