#include "shell.h"

static int		fork_child(t_env *e, pid_t pid)
{
	t_job		*son;

//	while (is_aggregator(e, RED_INDEX) || is_heredoc(e, RED_INDEX))
	while (RED_INDEX && !is_redir_pipe(e, RED_INDEX) && !is_operator(e, RED_INDEX)
		   && !is_output_redir(e, RED_INDEX))
		struct_find_red(e);
	if (!(son = ft_new_job(e->jobs, pid)))
		return (ft_error(SH_NAME, "malloc failed", NULL));
	e->jobs = son;
	return (1);
}

static int		ft_fork_exec(char *exec, char **cmd, t_env *e)
{
	pid_t		pid;

	if ((pid = fork()) < 0)
		ft_error(SH_NAME, "failed to fork process", NULL);
	if (pid)
	{
		++e->child_running;
		ft_close(FD.fd[1]);
		ft_close(FD.in);
	}
	else
	{
		if (redirection_before_cmd(e) == -1)
			exit(0);
		ft_redirect(FD.in, STDIN_FILENO);
//		dup2(FD.stdout, STDOUT_FILENO);
		execve(exec, &cmd[0], e->env);
	}
	return (fork_child(e, pid));
}

int				ft_exec(char **cmd, t_env *e)
{
	int		ret;
	char	**paths;
	char	*exec;

	ret = 0;
	exec = NULL;
	paths = ft_find_paths(e->env);
	exec = ft_find_exec(paths, cmd[0]);
	if (!exec || access(exec, F_OK))
	{
		strfree(&exec);
		ft_free_tab(paths);
		paths = NULL;
		return (ft_error(cmd[0], "Command not found", NULL));
	}
	if (access(exec, X_OK | R_OK) == 0 || ft_issticky(exec))
		ret = ft_fork_exec(exec, cmd, e);
	else
		ret = ft_error(exec, "Permission denied", NULL);
	ft_free_tab(paths);
	paths = NULL;
	strfree(&exec);
	return (ret);
}

static int		exec_cmd_bis(t_env *e, char **cmd)
{
	int		ret;

	ret = 0;
	if (ft_is_builtin(cmd[0]))
	{
		ret = ft_exec_builtin(e, cmd);
		reset_last_ret(e, ((ret == 1) ? 0 : 127));

	}
	else
	{
		ft_exec(cmd, e);
		ret = ft_waitlogix(e);
	}
	return (ret);
}

int				ft_exec_cmd(t_env *e, char **cmd)
{
	int			ret;

	ret = 0;
	e->cmd_len = ft_tablen(cmd);
	tcaps_reset(e);
	if (e->cmd_len)
		ret = exec_cmd_bis(e, cmd);
	else
		return (-1);
	e->cmd_len = 0;
	return (ret);
}
