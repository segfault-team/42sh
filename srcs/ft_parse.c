/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 18:55:15 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/06 18:47:17 by lfabbro          ###   ########.fr       */
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
	else if (ft_strequ(e->cmd[0], "history") && ++ret)
		ft_history(e);
	return (ret);
}

int				ft_exec_cmd(t_env *e, char *cmds, int in, int fd[2])
{
	int		ret;
	int		k;
	char	*tmp;

	ret = 0;
	tmp = NULL;
	e->cmd = ft_strsplit_quote(cmds, ' ');
	e->magic = struct_strsplit_quote(cmds, ' ');
	e->cat = ft_cmds_split(e);
	magic_type(e);
	e->cmd_len = ft_tablen(e->cmd);
	k = -1;
	while (e->cmd[++k])
		if (e->cmd[k][0] == '~')
		{
			tmp = ft_tilde(e, e->cmd[k]);
			free(e->cmd[k]);
			e->cmd[k] = tmp;
		}
	if (e->cmd_len)
	{
		if ((ret = ft_exec_builtin(e)))
			;
		else
			ret = ft_exec(e->cmd, e->env, in, fd);
	}
	ft_check_history(e);
	ft_free_tab(e->cmd);
	magic_free(e);
	e->cmd = NULL;
	e->cmd_len = 0;
	return (ret);
}

int				ft_split_pipes(t_env *e, char *cmds_i)
{
	int		i;
	int		in;
	int		fd[2];
	int		ret;
	char	**pipes;

	i = -1;
	in = STDIN_FILENO;
	pipes = ft_strsplit_quote(cmds_i, '|');
	while (pipes[++i + 1])
	{
	//	ft_printf("pipe[%d]: %s\n", i, pipes[i]);
		if (pipe(fd) < 0)
		{
			ft_free_tab(pipes);
			return (ft_error(SH_NAME, "Pipe failed.", NULL));
		}
		ret = ft_exec_cmd(e, pipes[i], in, fd);
		in = fd[0];
	}
	//ft_printf("pipe[%d]: %s\n", i, pipes[i]);
	fd[1] = STDOUT_FILENO;
	ret = ft_exec_cmd(e, pipes[i], in, fd);
	ft_free_tab(pipes);
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
				ret = ft_split_pipes(e, cmds[i]);
			}
			else
				ft_error(NULL, "Unmatched quote", NULL);
		}
	}
	ft_free_tab(cmds);
	ft_triple_free(e);
	return (ret);
}

char	*ft_tilde(t_env *e, char *current)
{
	char	*ret;
	char	*home;

	if (!(home = ft_getenv(e->env, "HOME")))
		return (NULL);
	ret = ft_strjoin(home, &current[1]);
	free(home);
	return (ret);
}
