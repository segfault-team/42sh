#include "shell.h"

int		ft_replace_dots(char *path, char *str, int *i)
{
	if (*path == '.' && (!path[1] || path[1] == '.' || path[1] == '/'))
	{
		if (!path[1] || path[1] == '/')
			*i = *i - 1;
		else if (path[1] == '.')
			*i = *i - 2;
		while (*i > 0 && str[*i] != '/')
			*i = *i - 1;
		if (*i < 0)
			*i = 0;
		return (1);
	}
	else
		return (0);
}

char	*ft_processpath(char *path)
{
	char	*str;
	int		i;

	str = ft_strnew(ft_strlen(path));
	if (!str)
		return (path);
	i = 0;
	while (*path)
	{
		if (!ft_replace_dots(path, str, &i))
		{
			str[i] = *path;
			i++;
			str[i] = '\0';
		}
		else if (path[1] == '.')
			path++;
		path++;
	}
	str[i] = '\0';
	if (!*str)
		str = ft_strcpy(str, "/");
	return (str);
}

char	*ft_create_path(char **paths, int process)
{
	char *tmp;
	char *tmp2;

	if (paths[1][0] != '/')
	{
		if (ft_strlen(paths[0]) &&
			paths[0][ft_strlen(paths[0]) - 1] != '/')
			tmp = ft_strjoin(paths[0], "/");
		else
			tmp = ft_strdup(paths[0]);
		tmp2 = ft_strjoin(tmp, paths[1]);
		ft_strdel(&tmp);
	}
	else
		tmp2 = ft_strdup(paths[1]);
	ft_remove_usless_slash(tmp2);
	if (process)
	{
		tmp = ft_processpath(tmp2);
		ft_strdel(&tmp2);
		tmp2 = tmp;
	}
	return (tmp2);
}

char	*ft_save_oldpwd(char **argv, t_env *e)
{
	char *ret;

	ret = NULL;
	if ((ret = ft_getenv(e->env, "PWD")) == NULL)
	{
		ret = getcwd(NULL, 0);
		ft_setenv(&e->env, "OLDPWD", ret);
	}
	return (ret);
}

int		ft_pre_chdir(char **tmp, char **a, char *dir, t_env *e)
{
	ft_fill_array((void **)tmp, ft_save_oldpwd(a, e),
		dir, NULL);
	tmp[1] = ft_create_path(tmp, 1);
	return (chdir(tmp[1]));
}
