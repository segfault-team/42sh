/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:08 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/07 00:08:57 by lfabbro          ###   ########.fr       */
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
	if ((value = ft_find_value(env, "PATH")) == NULL)
		paths = ft_strsplit(PATH, ':');
	else
	{
		paths = ft_strsplit(value, ':');
		free(value);
	}
	return (paths);
}

static int		ft_fork_exec(char *exec, char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if ((pid = fork()) < 0)
	{
		ft_error("fork", "failed to fork process", NULL);
	}
	else if (pid == 0)
	{
		execve(exec, &cmd[0], env);
	}
	waitpid(pid, &status, WUNTRACED);
	ft_handle_ret_signal(status);
	return (status);
}

int				ft_exec(char **cmd, char **env)
{
	int		status;
	char	**paths;
	char	*exec;

	status = 0;
	exec = NULL;
	paths = ft_find_paths(env);
	exec = ft_find_exec(paths, cmd[0]);
	if (access(exec, F_OK))
	{
		free(exec);
		ft_free_tab(paths);
		return (ft_error(cmd[0], "Command not found", NULL));
	}
	if (access(exec, X_OK | R_OK) == 0 || ft_issticky(exec))
		status = ft_fork_exec(exec, cmd, env);
	else
		ft_error(exec, "Permission denied", NULL);
	ft_free_tab(paths);
	free(exec);
	return (status);
}
