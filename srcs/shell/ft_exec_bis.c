#include "shell.h"

int		print_command_not_found(char *cmd, t_env *e)
{
	char *number;
	char *string;

	if (e->raw)
	{
		number = ft_itoa(-e->raw);
		string = ft_strjoin("line ", number);
		ft_error(cmd, string, "Command not found");
		ft_strdel(&number);
		ft_strdel(&string);
	}
	else
		ft_error(cmd, "Command not found", NULL);
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
		if (closedir(dir))
			ft_error("closedir", "failed closing dir", paths);
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
	if ((cmd[0] == '.' || cmd[0] == '/'))
		return (ft_isexec(cmd) ? ft_strdup(cmd) : NULL);
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

void	ft_close(int fd)
{
	if (fd != 1 && fd != 0)
	{
		if (close(fd) == -1)
			ft_error("IO stream error.\n", NULL, NULL);
	}
}
