/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:13 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/10 14:56:08 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		add_job(t_env *e, pid_t pid)
{
	t_job		*son;

	if (!(son = ft_new_job(e->jobs, pid)))
		return (ft_error(NULL, "malloc failed", NULL));
	e->jobs = son;
	return (1);
}

int				ft_fork_exec(char *exec, char **cmd, t_env *e)
{
	pid_t		pid;

	if ((redirection_before_cmd(e)) < 0)
	{
		ft_dupp(e);
		ft_close(FD.fd[1]);
		return (1);
	}
	if ((RED_INDEX != e->len_mag || is_next_redir(e, RED_INDEX) != -1)
		&& !e->is_out_close)
		ft_close(FD.fd[1]);
	if (ERRCODE && manage_err(e) && ft_dupp(e))
		return (-1);
	if ((pid = fork()) < 0)
		ft_error(NULL, "failed to fork process", NULL);
	if (!pid)
	{
		ft_redirect(FD.in, STDIN_FILENO);
		execve(exec, &cmd[0], e->env);
		exit(0);
	}
	++e->child_running;
	ft_dupp(e);
	return (add_job(e, pid));
}

static int		ft_exec(char **cmd, t_env *e, char *exec, int ret)
{
	char		**paths;
	struct stat	lstat;

	ft_bzero(&lstat, sizeof(struct stat));
	paths = ft_find_paths(e->env);
	if (!(exec = ft_find_exec(paths, cmd[0])))
	{
		if (paths)
			ft_free_tab(paths);
		print_command_not_found(cmd[0], e);
	}
	else
		stat(exec, &lstat);
	if (!ERRCODE && (!exec || access(exec, F_OK) || S_ISDIR(lstat.st_mode)))
	{
		strfree(&exec);
		if (paths)
			ft_free_tab(paths);
		paths = NULL;
		e->cmd_ok = 0;
		print_command_not_found(cmd[0], e);
	}
	else
		e->cmd_ok = 1;
	if (paths && !ERRCODE)
		ft_free_tab(paths);
	paths = NULL;
	return (ft_exec_bis(cmd, e, exec, ret));
}

static int		exec_cmd_bis(t_env *e, char **cmd)
{
	int		ret;

	ret = 0;
	if (ft_is_builtin(cmd[0]) && !e->env_exec)
	{
		ret = ft_exec_builtin(e, cmd, 0);
		e->last_cmd_ret = (ret > 0) ? 0 : 1;
		add_job(e, -1);
	}
	else
		ret = ft_exec(cmd, e, NULL, 0);
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
