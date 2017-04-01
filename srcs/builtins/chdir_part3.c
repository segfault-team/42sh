#include "shell.h"

char	*ft_repstr(char **argv, char *s1, char *s2, t_env *e)
{
	char	*fraiche;
	char	*pwd;
	char	*ptr[2];

	pwd = ft_getenv(e->env, "PWD");
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
	ft_putstr_fd("cd: -", 2);
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
	if ((*argv)[i][0] == '-' && (*argv)[i][1] == '-')
		i++;
	*argv = &(*argv)[i - 1];
	return (opt);
}
