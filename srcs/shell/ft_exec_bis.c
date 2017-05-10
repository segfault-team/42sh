/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:14 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/08 23:43:07 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_exec_bis(char **cmd, t_env *e, char *exec, int ret)
{
	if (!ERRCODE && (!exec || (access(exec, X_OK | R_OK) == -1
				&& !ft_issticky(exec))))
	{
		ret = -1;
		set_error(e, PERM_DENIED, exec);
		e->last_cmd_ret = 126;
	}
	ret = ft_fork_exec(exec, cmd, e);
	strfree(&exec);
	return (ret);
}

int		print_command_not_found(char *cmd, t_env *e)
{
	char *number;
	char *string;

	if (e->raw)
	{
		number = ft_itoa(-e->raw);
		string = ft_strjoin("line ", number);
		if (e->env_exec || (cmd && (cmd[0] == '/' || cmd[0] == '.')))
			set_error(e, NSFOD, cmd);
		else
			set_error(e, CMD_NF, cmd);
		e->last_cmd_ret = 127;
		ft_strdel(&number);
		ft_strdel(&string);
	}
	else
	{
		if (e->env_exec || (cmd && (cmd[0] == '/' || cmd[0] == '.')))
			set_error(e, INVALID_FILE, cmd);
		else
			set_error(e, CMD_NF, cmd);
		e->last_cmd_ret = 127;
	}
	return (-1);
}

char	*ft_find_exec_readdir(char *paths, char *cmd)
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
		closedir(dir);
	}
	return (exec);
}

char	*ft_find_exec(char **paths, char *cmd)
{
	char			*exec;
	char			*path;
	char			*tmp;
	int				i;

	i = -1;
	exec = NULL;
	path = NULL;
	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd && (cmd[0] == '.' || cmd[0] == '/'))
		return (ft_strdup(cmd));
	while (paths && paths[++i])
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

char	**ft_find_paths(char **env)
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
