/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:33:14 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/05 21:40:27 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include <sys/stat.h>

static int	ft_chdir_error(char *path)
{
	struct stat	buf;

	if (access(path, F_OK) == -1)
		return (ft_error("cd", "No such file or directory", path));
	lstat(path, &buf);
	if (!S_ISDIR(buf.st_mode))
		return (ft_error("cd", "Not a directory", path));
	if (access(path, X_OK | R_OK) == -1)
		return (ft_error("cd", "Permission denied", path));
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

int			ft_chdir(t_env *e, char **cmd)
{
	size_t	len;

	len = ft_tablen(cmd);
	if (len > 2)
		return (ft_error("cd", "too many arguments", NULL));
	if (len == 1)
	{
		if (!ft_issetenv(e->env, "HOME") && e->home == NULL)
			return (ft_error("cd", "no home set", NULL));
		return (ft_chdir_env(e, e->home));
	}
	if (ft_strequ(cmd[1], "-"))
	{
		strfree(&cmd[1]);
		if ((cmd[1] = ft_getenv(e->env, "OLDPWD")) == NULL)
			return (ft_error("cd", "no oldpwd in env", NULL));
	}
	return (ft_chdir_env(e, cmd[1]));
}
