/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 18:55:15 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/13 19:37:26 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*ft_tilde(t_env *e, char *current)
{
	char	*ret;
	char	*home;

	if (!(home = ft_getenv(e->env, "HOME")))
		return (NULL);
	ret = ft_strjoin(home, &current[1]);
	free(home);
	return (ret);
}

static int		ft_subs_tilde(t_env *e)
{
	int		k;
	char	*tmp;

	k = -1;
	tmp = NULL;
	while (e->cmd[++k])
		if (e->cmd[k][0] == '~')
		{
			tmp = ft_tilde(e, e->cmd[k]);
			free(e->cmd[k]);
			e->cmd[k] = tmp;
		}
	return (0);
}

static char		**ft_trim_split_cmd(t_env *e)
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
	else if (ft_strequ(e->cmd[0], "history") && ++ret)
		ft_history(e);
	return (ret);
}

int				ft_exec_cmd(t_env *e, char **cmd)
{
	int		ret;

	ret = 0;
	e->cmd_len = ft_tablen(cmd);
	ft_subs_tilde(e);
	if (e->cmd_len)
	{
		if ((ret = ft_exec_builtin(e)))
			;
		else
			ret = ft_exec(cmd, e);
	}
	ft_check_history(e);
	e->cmd_len = 0;
	return (ret);
}

int				ft_iter_pipes(t_env *e, char *cmds_i)
{
	int		i;
	int		ret;

	i = -1;
	FD.in = STDIN_FILENO;
	e->cmd = ft_strsplit_quote(cmds_i, ' ');
	e->magic = struct_strsplit_quote(cmds_i, ' ');
	e->cat = ft_cmds_split(e);
/*	for (int j = 0 ; e->cat[j]; j++)
		for (int k = 0; e->cat[j][k]; k++)
			ft_printf("cat[%d][%d] : %s\n", j, k, e->cat[j][k]);*/
	magic_type(e);
	while (e->cat[++i + 1] && ret != -1)
		ret = redir_exec_open(i, e); // WIP
	ret = redir_last_cmd(i, e);
	if (FD.last_red)
	{
		free(FD.last_red);
		FD.last_red = NULL;
	}
	ft_triple_free(e);
	magic_free(e);
	return (ret);
}

int				ft_parse_line(t_env *e)
{
	int		i;
	int		ret;
	char	**cmds;

	i = -1;
	ret = 0;
	if ((cmds = ft_trim_split_cmd(e)) != NULL)
	{
		while (cmds[++i])
		{
			if (ft_matchquotes(cmds[i]) == 0)
				ret = ft_iter_pipes(e, cmds[i]);
			else
				ft_error(NULL, "Unmatched quote", NULL);
			e->check_remove_tab = 0;
		}
	}
	ft_free_tab(cmds);
	return (ret);
}
