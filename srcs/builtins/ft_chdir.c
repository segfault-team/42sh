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

void	ft_array_strdel(char **array)
{
	while (array && *array)
	{
		ft_strdel(array);
		array++;
	}
}

void	ft_fill_array(void **array, void *a1, void *a2, void *a3)
{
	array[0] = NULL;
	if (a1)
	{
		array[0] = a1;
		array[1] = NULL;
	}
	if (a1 && a2)
	{
		array[1] = a2;
		array[2] = NULL;
	}
	if (a1 && a2 && a3)
	{
		array[2] = a3;
		array[3] = NULL;
	}
}

void	ft_replace_word(char **s1, char *s2, char **s3, int i)
{
	while (s2 && *s2)
	{
		**s1 = *s2;
		*s1 += 1;
		s2 += 1;
	}
	*s3 += i - 1;
}

char	*ft_repstr(char **argv, char *s1, char *s2, t_env *e)
{
	char	*fraiche;
	char	*pwd;
	char	*ptr[2];

	pwd = ft_getenv(e->env, "OLDPWD");
	fraiche = ft_strnew(ft_strlen(s1) + ft_strlen(pwd) + 1);
	ptr[0] = fraiche;
	ptr[1] = pwd;
	while (*pwd)
	{
		if (!ft_strncmp(pwd, s1, ft_strlen(s1)) && *s2)
			ft_replace_word(&fraiche, s2, &pwd, ft_strlen(s1));
		else
		{
			*fraiche = *pwd;
			fraiche++;
		}
		pwd++;
	}
	if (!ft_strcmp(ptr[1], ptr[0]))
		ft_strdel(&ptr[0]);
	ft_strdel(&ptr[1]);
	return (ptr[0]);
}

void	ft_remove_usless_slash(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (str && i > 0 && str[i] == '/')
	{
		str[i] = '\0';
		i--;
	}
}

int		ft_print_cd_opt_error(char option)
{
	ft_putstr_fd("Yoloshell: cd: -", 2);
	ft_putchar_fd(option, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("cd: usage: cd [-L|-P] [dir]\n", 2);
	return (-1);
}

int		ft_option_p(char *s)
{
	int i;
	int	ret;

	i = 1;
	ret = 0;
	if (*s != '-')
		return (0);
	while (s[i])
	{
		if (s[i] == 'P')
			ret = 1;
		else if (s[i] == 'L')
			ret = 2;
		else
			return (ft_print_cd_opt_error(s[i]));
		i++;
	}
	return (ret);
}

int		ft_cd_check_option(char ***argv)
{
	int opt;
	int i;

	opt = 0;
	i = 1;
	while ((*argv)[i] && (*argv)[0] && (*argv)[i][1]
		&& (*argv)[i][0] == '-' && (*argv)[i][1] != '-')
	{
		opt = ft_option_p((*argv)[i]);
		if (opt == -1)
			return (opt);
		i++;
	}
	*argv = &(*argv)[i - 1];
	return (opt);
}

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

	str = (char *)malloc(ft_strlen(path) + 1);
	if (!str)
		ft_printfd(2, "MANAGE ERROR\n");
	i = 0;
	while (*path)
	{
		if (ft_replace_dots(path, str, &i))
		{
			if (path[1] == '.')
				path++;
		}
		else
		{
			str[i] = *path;
			i++;
			str[i] = '\0';
		}
		path++;
	}
	str[i] = '\0';
	if (!*str)
		str = ft_strcpy(str, "/");
	return (str);
}

char	*ft_create_path(char **paths)
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
	tmp = ft_processpath(tmp2);
	ft_strdel(&tmp2);
	return (tmp);
}

char	*ft_save_oldpwd(char **argv, t_env *e)
{
	char *ret;

	ret = NULL;
	if ((ret = ft_getenv(e->env, "PWD")) == NULL)
		ft_setenv(&e->env, "OLDPWD", ret);
	return (ret);
}

int		ft_pre_chdir(char **tmp, char **a, char *dir, t_env *e)
{
	ft_fill_array((void **)tmp, ft_save_oldpwd(a, e),
		dir, ft_save_oldpwd(a, e));
	tmp[1] = ft_create_path(tmp);
	return (chdir(tmp[1]));
}

int		ft_chdir(char **argv, char *dir, t_env *e, int option)
{
	char	buff[PATH_MAX];
	char	*cwd;
	char	*args[3];
	int		retval;
	char	*tmp[4];

	retval = ft_pre_chdir((char **)tmp, argv, dir, e);
	if (option == 1)
		cwd = getcwd(buff, PATH_MAX);
	else
		cwd = tmp[1];
	ft_fill_array((void **)args, ft_strdup("PWD"), ft_strdup(cwd), NULL);
	if (!retval)
		ft_setenv(&e->env, "PWD", args[1]);
	else
	{
		ft_array_strdel(args);
		ft_fill_array((void **)args, ft_strdup("OLDPWD"),
			ft_strdup(tmp[2]), NULL);
		ft_setenv(&e->env, "OLDPWD", args[1]);
	}
	ft_array_strdel(args);
	ft_array_strdel(tmp);
	return (retval);
}

int		ft_cd_bis(char **argv, t_env *e, char *home, int opt)
{
	char	**tmp;

	tmp = NULL;
	if (argv[1])
	{
		home = ft_strdup(argv[1]);
		if (argv[2] && *argv[2])
		{
			ft_strdel(&home);
			home = ft_repstr(argv, argv[1], argv[2], e);
		}
		if (!home)
			return (ft_error("cd", "string not in pwd:", argv[1]));
	}
	else
	{
		if (!ft_issetenv(e->env, "HOME") && e->home == NULL)
			return (ft_error("cd", "no home set", NULL));
		home = ft_strdup(e->home);
	}
	if (ft_chdir(argv, home, e, opt) == -1)
		ft_chdir_error(home);
	ft_strdel(&home);
	ft_free_tab(tmp);
	return (1);
}

int		ft_cd_oldpwd(char **argv, t_env *e, int option)
{
	int		ret;
	char	**new;

	ret = -1;
	new = (char **)malloc(3 * sizeof(char*));
	new[0] = ft_strdup(argv[0]);
	new[2] = NULL;
	if ((new[1] = ft_getenv(e->env, "OLDPWD")) == NULL)
		ret = ft_error("cd", "no oldpwd in env", NULL);
	else
	{
		ft_putendl(new[1]);
		ret = ft_cd_bis(new, e, new[1], option);
	}
	ft_free_tab(new);
	return (ret);
}

int		ft_cd(t_env *e, char **cmd)
{
	char	*home;
	int		option;

	if ((option = ft_cd_check_option(&cmd)) == -1)
		return (-1);
	if ((home = cmd[1]) == NULL)
	{
		if (!ft_issetenv(e->env, "HOME") && e->home == NULL)
			return (ft_error("cd", "no home set", NULL));
		home = e->home;
		if (ft_chdir(cmd, home, e, 0) == -1)
			ft_chdir_error(home);
	}
	else if (!ft_strcmp(cmd[1], "-"))
		return (ft_cd_oldpwd(cmd, e, option));
	else if (ft_tablen(cmd) > 3)
		return (ft_error("cd", "too many arguments", NULL));
	else
		return (ft_cd_bis(cmd, e, home, option));
	return (0);
}
