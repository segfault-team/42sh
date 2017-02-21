/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 18:55:15 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/21 15:27:27 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*ft_tilde(t_env *e, char *current)
{
	char	*ret;
	char	*home;

	if (!(home = ft_getenv(e->env, "HOME")))
		return (NULL);
	ret = ft_strjoin(home, &current[1]);
	strfree(&home);
	return (ret);
}

int		ft_subs_tilde(t_env *e)
{
	int		k;
	char	*tmp;

	k = -1;
	tmp = NULL;
	while (e->cmd[++k])
		if (e->cmd[k][0] == '~')
		{
			tmp = ft_tilde(e, e->cmd[k]);
			strfree(&e->cmd[k]);
			e->cmd[k] = tmp;
		}
	return (0);
}

char		**ft_trim_split_cmd(t_env *e)
{
	char	**cmds;
	char	*trline;

	trline = ft_strxtrim_quote(e->line, '\t');
	cmds = ft_strsplit_quote(trline, ';');
	ft_strdel(&trline);
	return (cmds);
}

int		ft_exec_builtin(char **cmd, t_env *e)
{
	char	ret;

	ret = 0;
	ft_redir_builtin(e);
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
		ft_echo(e, cmd);
	else if (ft_strequ(e->cmd[0], "where") && ++ret)
		ft_where(e);
	else if (ft_strequ(e->cmd[0], "history") && ++ret)
		ft_history(e);
	//ft_close(FD.fd[1]);
	//ft_close(FD.in);
	return (ret);
}

void			ft_putmagic(t_env *e)
{
	int		i = -1;

	while (e->magic[++i].cmd)
	{
		ft_printfd(2, "cmd[%d]: %s		type: %s\n", i, e->magic[i].cmd, e->magic[i].type);
	}
}

int				ft_iter_pipes(t_env *e, char *cmds_i)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	FD.in = STDIN_FILENO;
	e->cmd = ft_strsplit_quote(cmds_i, ' ');
	e->magic = struct_strsplit_quote(cmds_i, ' ');
	e->cat = ft_cmds_split(e);
	magic_type(e);
	/*
	ft_printf("---MAGIC---\n");
	ft_putmagic(e);
	ft_printf("-----------\n");
	ft_printf("---CAT-----\n");
	*/
	while (e->cat[++i + 1] && ret != -1)
	{
		//ft_printf("cat[%d]:\n", i);
		//ft_puttab(e->cat[i]);
		ret = redir_exec_open(i, e);
	}
	//ft_printf("cat[%d]:\n", i);
	//ft_puttab(e->cat[i]);
	//ft_printf("-----------\n");
	ret = redir_last_cmd(i, e);
	ft_check_history(e);
	ft_triple_free(e);
	magic_free(e);
	RED_INDEX = 0;
	ft_tabfree(e->cmd);
	e->cmd = NULL;
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
		}
	}
	ft_free_tab(cmds);
	return (ret);
}
