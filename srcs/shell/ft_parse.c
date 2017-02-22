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

int		ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv") ||
		!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "where") || !ft_strcmp(cmd, "history"))
		return (1);
	return (0);
}

int		ft_exec_builtin(t_env *e, char **cmd)
{
	char	ret;

	ret = 0;
	if (redir_check_red(e, "|") || redir_check_red(e, ">") || redir_check_red(e, ">>"))
	{
		if (/*ft_redirect(FD.in, STDIN_FILENO) ||
			 */ft_redirect(FD.fd[1], STDOUT_FILENO))
			return (-1);
	}
	if (!ft_strcmp(cmd[0], "exit") && ++ret)
		ft_exit(e);
	else if (!ft_strcmp(cmd[0], "env") && ++ret)
		ft_env(e);
	else if (!ft_strcmp(cmd[0], "setenv") && ++ret)
		ft_setenv_blt(e);
	else if (!ft_strcmp(cmd[0], "unsetenv") && ++ret)
		ft_unsetenv_blt(e);
	else if (!ft_strcmp(cmd[0], "cd") && ++ret)
		ft_chdir(e);
	else if (!ft_strcmp(cmd[0], "echo") && ++ret)
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "where") && ++ret)
		ft_where(e);
	else if (!ft_strcmp(cmd[0], "history") && ++ret)
		ft_history(e);
	return (ret);
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
/*
  for (int j = 0 ; e->cat[j]; j++)
		for (int k = 0; e->cat[j][k]; k++)
			ft_printf("cat[%d][%d] : %s\n", j, k, e->cat[j][k]);
*/
	magic_type(e);
	while (e->cat[++i + 1] && ret != -1)
	{
		ret = redir_exec_open(i, e);
		dup2(FD.stdin, STDIN_FILENO);
		dup2(FD.stdout, STDOUT_FILENO);
		dup2(FD.stderr, STDERR_FILENO);
	}
	ret = redir_last_cmd(i, e);
	ft_check_history(e);
	ft_triple_free(e);
	magic_free(e);
	RED_INDEX = 0;
	ft_free_tab(e->cmd);
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

