#include "shell.h"

int		ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "env") ||
			!ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv") ||
			!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") ||
			!ft_strcmp(cmd, "where") || !ft_strcmp(cmd, "history") ||
			!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

int		ft_exec_builtin(t_env *e, char **cmd)
{
	char	ret;
	int		mem;

	mem = RED_INDEX;
	ret = 0;
	if (redirection_before_cmd(e) < 1)
		return (-1);
	ft_redirect(FD.in, STDIN_FILENO);
	if (!ft_strcmp(cmd[0], "exit") && ++ret)
		ft_exit(e);
	else if (!ft_strcmp(cmd[0], "env") && ++ret)
		ret = ft_env(e, cmd);
	else if (!ft_strcmp(cmd[0], "setenv") && ++ret)
		ret = ft_setenv_blt(e, cmd);
	else if (!ft_strcmp(cmd[0], "unsetenv") && ++ret)
		ret = ft_unsetenv_blt(e, cmd);
	else if (!ft_strcmp(cmd[0], "cd") && ++ret)
		ret = ft_cd(e, cmd);
	else if (!ft_strcmp(cmd[0], "pwd") && ++ret)
		ret = ft_pwd(e, cmd);
	else if (!ft_strcmp(cmd[0], "echo") && ++ret)
		ret = ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "where") && ++ret)
		ret = ft_where(e, cmd);
	else if (!ft_strcmp(cmd[0], "history") && ++ret)
		ret = ft_history(e, cmd, 1);
	RED_INDEX = mem;
	ft_close(FD.fd[1]);
	ft_close(STDOUT_FILENO);
//	dup2(FD.stdin, STDIN_FILENO);
//	dup2(FD.stdout, STDOUT_FILENO);
//	dup2(FD.stderr, STDERR_FILENO);
	return (ret);
}

int		ft_waitsons(t_env *e)
{
	t_job		*tmp;
	int			status;

	tmp = NULL;
	status = 0;
	while (e->jobs)
	{
		waitpid(e->jobs->pid, &status, WUNTRACED);
		ft_handle_ret_signal(status);
		tmp = e->jobs->next;
		free(e->jobs);
		e->jobs = tmp;
	}
	e->child_running = 0;
	e->jobs = NULL;
	if (!status)
		return (1);
	return (-1);
}

/*
** trline is now useless cause tab is not inserted (tcaps directives)
*/

char	**ft_trim_split_cmd(t_env *e)
{
	char	**cmds;
	char	*trline;

	if (!(trline = ft_strxtrim_quote(e->line, '\t')))
	{
		ft_printfd(2, "%s: syntax error near unexpected token \";;\"\n",
				SH_NAME);
		return (NULL);
	}
	cmds = ft_split_cmds(trline, ';');
	ft_strdel(&trline);
	return (cmds);
}
