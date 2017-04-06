#include "shell.h"

static int		ft_print_pwd_opt_error(char option)
{
	ft_putstr_fd("pwd: -", 2);
	ft_putchar_fd(option, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("cd: usage: pwd [-L|-P]\n", 2);
	return (-1);
}

static int		ft_option_pwd(char *s)
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
			return (ft_print_pwd_opt_error(s[i]));
		i++;
	}
	return (ret);
}

static int		ft_pwd_check_option(char ***argv)
{
	int opt;
	int i;

	opt = 0;
	i = 1;
	while ((*argv)[i] && (*argv)[0] && (*argv)[i][1]
		&& (*argv)[i][0] == '-' && (*argv)[i][1] != '-')
	{
		opt = ft_option_pwd((*argv)[i]);
		if (opt == -1)
			return (opt);
		i++;
	}
	*argv = &(*argv)[i - 1];
	return (opt);
}

int				ft_pwd(t_env *e, char **args)
{
	int		option;
	char	*cwd;

	if ((option = ft_pwd_check_option(&args)) == -1)
		return (-1);
	if (option == 1)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (ft_error("cd: error retrieving current directory: getcwd: "
				, "cannot access parent directories: "
				, "No such file or directory"));
	}
	else
		cwd = ft_getenv(e->env, "PWD");
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_strdel(&cwd);
	return (1);
}
