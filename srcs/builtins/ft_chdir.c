/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:33:14 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/16 09:31:52 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include <sys/stat.h>

static int	ft_chdir_error(char *path)
{
	struct stat	buf;

	if (access(path, F_OK) == -1)
		return (ft_error(path, "No such file or directory", NULL));
	lstat(path, &buf);
	if (!S_ISDIR(buf.st_mode))
		return (ft_error(path, "Not a directory", NULL));
	if (access(path, X_OK | R_OK) == -1)
		return (ft_error(path, "Permission denied", NULL));
	return (ft_error("cd", "Unknown error: ", path));
}

static int	ft_chdir_env(t_env *e, char *dir)
{
	char	*pwd;
	char	*oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	oldpwd = getcwd(oldpwd, 0);
	if (chdir(dir) == -1)
	{
		strfree(&oldpwd);
		return (ft_chdir_error(dir));
	}
	pwd = getcwd(pwd, 0);
	ft_setenv(&e->env, "OLDPWD", oldpwd);
	ft_setenv(&e->env, "PWD", pwd);
	strfree(&oldpwd);
	strfree(&pwd);
	return (0);
}

int			ft_chdir(t_env *e)
{
	if (e->cmd_len > 2)
		return (ft_error("cd", "too many arguments", NULL));
	if (e->cmd_len == 1)
	{
		if (!ft_issetenv(e->env, "HOME") && e->home == NULL)
			return (ft_error("cd", "no home set", NULL));
		return (ft_chdir_env(e, e->home));
	}
	if (ft_strequ(e->cmd[1], "-"))
	{
		strfree(&e->cmd[1]);
		if ((e->cmd[1] = ft_getenv(e->env, "OLDPWD")) == NULL)
			return (ft_error("cd", "no oldpwd in env", NULL));
	}
	return (ft_chdir_env(e, e->cmd[1]));
}
