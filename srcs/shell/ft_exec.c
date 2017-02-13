/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:08 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/13 19:44:29 by vlistrat         ###   ########.fr       */
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
			free(tmp);
			free(exec);
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
		free(value);
	}
	return (paths);
}

static int		ft_redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
		{
			if (close(oldfd) < 0)
				return (ft_error(SH_NAME, "Failed closing fd", NULL));
		}
		else
			return (ft_error(SH_NAME, "dup2 failed", NULL));
	}
	return (0);
}

void		ft_close(int fd)
{
	if (fd != 1 && fd != 0) {
		if (close(fd) == -1)
		{
//			ft_printf("fd : %d\n", fd);
			ft_error(SH_NAME, "Close failed on fd", NULL);
		}
	}
}


/*

	POSSIBLE SOLUTION POUR LES CMDS TYPE :
	ls > test1 > test2 > [...]


if (FD.last_red && !ft_strcmp(FD.last_red, ">") &&
			 e->magic[RED_INDEX].cmd)// && !ft_strcmp(e->magic[RED_INDEX].cmd, ">"))
	{
		if ((fd = open(cmd[0], TWO_RED_FLAGS, OPENFLAGS)) == -1)
			ft_printf("MANAGE ERROR");
		while (get_next_line(fd, &buf) > 0)
			write(FD.fd[1], &buf, (int)ft_strlen(buf));
		ft_close(fd);
	}

*/



static int		ft_fork_exec(char *exec, char **cmd, t_env *e)
{
	pid_t	pid;
	int		status;

	status = 0;
	if ((pid = fork()) < 0)
	{
		ft_error(SH_NAME, "failed to fork process", NULL);
	}
	if (pid == 0)
	{
		if (redir_check_red(e, "|"))
		{
			if (ft_redirect(FD.in, STDIN_FILENO) ||
				ft_redirect(FD.fd[1], STDOUT_FILENO))
				return (-1);
			FD.last_red = ft_strdup(e->magic[RED_INDEX].cmd);
			execve(exec, &cmd[0], e->env);
		}
		else
			execve(exec, &cmd[0], e->env);
		if (RED_INDEX > 0 && e->magic[RED_INDEX].cmd)
			FD.last_red = ft_strdup(e->magic[RED_INDEX].cmd);
	}
	ft_close(FD.fd[1]);
	ft_close(FD.in);
// manage this
	waitpid(pid, &status, WUNTRACED);
	ft_handle_ret_signal(status);
	return (status);
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
		free(exec);
		ft_free_tab(paths);
		return (ft_error(cmd[0], "Command not found", NULL));
	}
	if (access(exec, X_OK | R_OK) == 0 || ft_issticky(exec))
		status = ft_fork_exec(exec, cmd, e);
	else
		ft_error(exec, "Permission denied", NULL);
	ft_free_tab(paths);
	free(exec);
	return (status);
}
