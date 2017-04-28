/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_part1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:10:44 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:10:44 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	set_cwd(t_env *e, char **cwd, char *dir, int retval)
{
	char	*tmp[4];

	*cwd = getcwd(NULL, 0);
	if (!*cwd)
	{
		ft_error("cd: error retrieving current directory: getcwd: "
				, "cannot access parent directories: "
				, "No such file or directory");
		ft_fill_array((void **)tmp, ft_save_oldpwd(e),
				dir, ft_save_oldpwd(e));
		tmp[1] = ft_create_path(tmp, 0);
		*cwd = ft_strdup(tmp[1]);
		ft_array_strdel(tmp);
		retval = 1;
	}
	return (retval);
}

int			ft_chdir(char *dir, t_env *e, int option)
{
	char	*cwd;
	char	*args[3];
	int		retval;
	char	*tmp[4];

	cwd = NULL;
	retval = ft_pre_chdir((char **)tmp, dir, e);
	if (option == 1 || retval == -1)
		retval = set_cwd(e, &cwd, dir, retval);
	else
		cwd = ft_strdup(tmp[1]);
	ft_fill_array((void **)args, ft_strdup("PWD"), cwd, NULL);
	if (retval != -1)
	{
		ft_setenv(&e->env, "PWD", args[1]);
		ft_array_strdel(args);
		ft_fill_array((void **)args, ft_strdup("OLDPWD"),
			ft_strdup(tmp[0]), NULL);
		ft_setenv(&e->env, "OLDPWD", args[1]);
	}
	ft_array_strdel(args);
	ft_array_strdel(tmp);
	return (retval);
}

int			ft_cd_bis(char **argv, t_env *e, char *home, int opt)
{
	char	**tmp;

	tmp = NULL;
	if (argv[1])
	{
		home = ft_strdup(argv[1]);
		if (argv[2] && *argv[2])
		{
			ft_strdel(&home);
			home = ft_repstr(argv[1], argv[2], e);
		}
		if (!home)
			return (ft_error("cd", "string not in pwd:", argv[1]));
	}
	else
	{
		if (!(home = ft_getenv(e->env, "HOME")))
			return (ft_error("cd", "no home set", NULL));
	}
	if (ft_chdir(home, e, opt) == -1)
		ft_chdir_error(home);
	ft_strdel(&home);
	ft_free_tab(tmp);
	e->prompt = ft_create_prompt(e, STD_PROMPT);
	return (1);
}

int			ft_cd_oldpwd(char **argv, t_env *e, int option)
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
	e->prompt = ft_create_prompt(e, STD_PROMPT);
	return (ret);
}

int			ft_cd(t_env *e, char **cmd)
{
	char	*home;
	int		option;

	if ((option = ft_cd_check_option(&cmd)) == -1)
		return (-1);
	if ((home = cmd[1]) == NULL)
	{
		if (!(home = ft_getenv(e->env, "HOME")))
			home = ft_strdup(e->home);
		if (!home)
			return (ft_error("cd", "no home set", NULL));
		if (ft_chdir(home, e, 0) == -1)
			ft_chdir_error(home);
		ft_strdel(&home);
		e->prompt = ft_create_prompt(e, STD_PROMPT);
	}
	else if (!ft_strcmp(cmd[1], "-"))
		return (ft_cd_oldpwd(cmd, e, option));
	else if (ft_tablen(cmd) > 3)
		return (ft_error("cd", "too many arguments", NULL));
	else
		return (ft_cd_bis(cmd, e, home, option));
	return (1);
}
