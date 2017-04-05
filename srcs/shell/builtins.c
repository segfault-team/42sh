#include "shell.h"

static int	need_close_for_env(char **cmd)
{
	int	len;

	len = (int)ft_tablen(cmd);
	if (len == 1 ||
		(len == 2 && (!ft_strcmp(cmd[1], "-u") || !ft_strcmp(cmd[1], "-i"))))
		return (1);
	return (0);
}

int			ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv") ||
		!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "where") || !ft_strcmp(cmd, "history") ||
		!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

static int	ft_exec_builtin_bis(t_env *e, char **cmd, int ret)
{
	if (!ft_strcmp(cmd[0], "cd") && ++ret)
		return ((ret = ft_cd(e, cmd)));
	else if (!ft_strcmp(cmd[0], "pwd") && ++ret)
		return ((ret = ft_pwd(e, cmd)));
	else if (!ft_strcmp(cmd[0], "echo") && ++ret)
		return ((ret = ft_echo(cmd)));
	else if (!ft_strcmp(cmd[0], "where") && ++ret)
		return ((ret = ft_where(e, cmd)));
	else if (!ft_strcmp(cmd[0], "history") && ++ret)
		return ((ret = ft_history(e, cmd, 1)));
	return (ret);
}

int			ft_exec_builtin(t_env *e, char **cmd, int ret)
{
	if (redirection_before_cmd(e) < 1)
	{
		ft_close(FD.fd[1]);
		ft_dupp(e);
		return (-1);
	}
	ft_redirect(FD.in, STDIN_FILENO);
	if (!ft_strcmp(cmd[0], "exit") && ++ret)
		ret = ft_exit(e, cmd);
	else if (!ft_strcmp(cmd[0], "env") && ++ret)
		ret = ft_env(e, cmd);
	else if (!ft_strcmp(cmd[0], "setenv") && ++ret)
		ret = ft_setenv_blt(e, cmd);
	else if (!ft_strcmp(cmd[0], "unsetenv") && ++ret)
		ret = ft_unsetenv_blt(e, cmd);
	ret = ft_exec_builtin_bis(e, cmd, ret);
	if (ft_strcmp("env", cmd[0]) ||
		(need_close_for_env(cmd)))
		ft_close(FD.fd[1]);
	ft_dupp(e);
	return (ret);
}
