/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:08 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/28 17:44:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*ft_find_exec_readdir(char *paths, char *cmd)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*exec;

	exec = NULL;
	if ((dir = opendir(paths)) != NULL)
	{
		while ((dirent = readdir(dir)) != NULL)
		{
			if (ft_strequ(dirent->d_name, cmd))
			{
				exec = ft_strdup(dirent->d_name);
				break ;
			}
		}
		if (closedir(dir))
			ft_error("closedir", "failed closing dir", paths);
	}
	return (exec);
}

char			*ft_find_exec(char **paths, char *cmd)
{
	char			*exec;
	char			*path;
	char			*tmp;
	int				i;

	i = -1;
	exec = NULL;
	path = NULL;
	if ((cmd[0] == '.' || cmd[0] == '/'))
	{
		if (ft_isexec(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (paths[++i])
		if ((exec = ft_find_exec_readdir(paths[i], cmd)) != NULL)
		{
			tmp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(tmp, exec);
			strfree(&tmp);
			strfree(&exec);
			break ;
		}
	return (path);
}

char			**ft_find_paths(char **env)
{
	char	*value;
	char	**paths;

	paths = NULL;
	value = NULL;
	if ((value = ft_getenv(env, "PATH")) == NULL)
		paths = ft_strsplit(PATH, ':');
	else
	{
		paths = ft_strsplit(value, ':');
		strfree(&value);
	}
	return (paths);
}

void		ft_close(int fd)
{
	if (fd != 1 && fd != 0) {
		if (close(fd) == -1)
		{
			ft_error(SH_NAME, "Close failed on fd", NULL);
		}
	}
}

pid_t		singletonne(pid_t pid)
{
	static pid_t REAL = 0;

	if (pid != -42)
		REAL = pid;
	return (REAL);
}

static int		ft_fork_exec(char *exec, char **cmd, t_env *e)
{
	t_job	*son;
	pid_t	pid;

	if ((pid = fork()) < 0 || (singletonne(pid)) < 0)
	{
		ft_error(SH_NAME, "failed to fork process", NULL);
	}
	if (singletonne(-42))
	{
		ft_close(FD.fd[1]);
		ft_close(FD.in);
	}
	else
	{
		if (redir_check_red(e, "|") || redir_check_red(e, ">") || \
				redir_check_red(e, ">>"))
		{
			if (ft_redirect(FD.in, STDIN_FILENO) ||
				ft_redirect(FD.fd[1], STDOUT_FILENO))
				return (-1);
		}
		execve(exec, &cmd[0], e->env);
	}
	if ((son = ft_new_job(e->jobs, pid)) == NULL)
		return (ft_error(SH_NAME, "malloc failed", NULL));
	e->jobs = son;
	return (0);
}

int				ft_exec(char **cmd, t_env *e)
{
	int		status;
	char	**paths;
	char	*exec;

	status = 0;
	exec = NULL;
	paths = ft_find_paths(e->env);
	exec = ft_find_exec(paths, cmd[0]);
	if (access(exec, F_OK))
	{
		strfree(&exec);
		ft_free_tab(paths);
		paths = NULL;
		return (ft_error(cmd[0], "Command not found", NULL));
	}
	if (access(exec, X_OK | R_OK) == 0 || ft_issticky(exec))
		status = ft_fork_exec(exec, cmd, e);
	else
		ft_error(exec, "Permission denied", NULL);
	ft_free_tab(paths);
	paths = NULL;
	strfree(&exec);
	return (status);
}

int				ft_exec_cmd(t_env *e, char **cmd)
{
	int		ret;

	ret = 0;
	e->cmd_len = ft_tablen(cmd);
	ft_subs_tilde(e);
	tcaps_reset();
	if (e->cmd_len)
	{
		if (ft_is_builtin(cmd[0]))
			ret = ft_exec_builtin(e, cmd);
		else
			ret = ft_exec(cmd, e);
	}
	e->cmd_len = 0;
	return (ret);
}
